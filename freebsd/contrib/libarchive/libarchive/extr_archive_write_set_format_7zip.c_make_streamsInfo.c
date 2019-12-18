#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct file {int size; struct file* next; } ;
struct coder {scalar_t__ codec; int prop_size; scalar_t__* props; } ;
struct archive_write {scalar_t__ format_data; } ;
struct TYPE_2__ {struct file* first; } ;
struct _7zip {TYPE_1__ file_list; scalar_t__ total_number_nonempty_entry; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_Z_RUN ; 
 scalar_t__ _7Z_COPY ; 
 int /*<<< orphan*/  archive_be64enc (scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  archive_le32enc (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ compress_out (struct archive_write*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int enc_uint64 (struct archive_write*,int) ; 
 int kCRC ; 
 int kCodersUnPackSize ; 
 int kEnd ; 
 int kFolder ; 
 int kPackInfo ; 
 int kSize ; 
 int kUnPackInfo ; 
 int make_substreamsInfo (struct archive_write*,struct coder*) ; 

__attribute__((used)) static int
make_streamsInfo(struct archive_write *a, uint64_t offset, uint64_t pack_size,
    uint64_t unpack_size, int num_coder, struct coder *coders, int substrm,
    uint32_t header_crc)
{
	struct _7zip *zip = (struct _7zip *)a->format_data;
	uint8_t codec_buff[8];
	int numFolders, fi;
	int codec_size;
	int i, r;

	if (coders->codec == _7Z_COPY)
		numFolders = (int)zip->total_number_nonempty_entry;
	else
		numFolders = 1;

	/*
	 * Make PackInfo.
	 */
	r = enc_uint64(a, kPackInfo);
	if (r < 0)
		return (r);

	/* Write PackPos. */
	r = enc_uint64(a, offset);
	if (r < 0)
		return (r);

	/* Write NumPackStreams. */
	r = enc_uint64(a, numFolders);
	if (r < 0)
		return (r);

	/* Make Size. */
	r = enc_uint64(a, kSize);
	if (r < 0)
		return (r);

	if (numFolders > 1) {
		struct file *file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->size == 0)
				break;
			r = enc_uint64(a, file->size);
			if (r < 0)
				return (r);
		}
	} else {
		/* Write size. */
		r = enc_uint64(a, pack_size);
		if (r < 0)
			return (r);
	}

	r = enc_uint64(a, kEnd);
	if (r < 0)
		return (r);

	/*
	 * Make UnPackInfo.
	 */
	r = enc_uint64(a, kUnPackInfo);
	if (r < 0)
		return (r);

	/*
	 * Make Folder.
	 */
	r = enc_uint64(a, kFolder);
	if (r < 0)
		return (r);

	/* Write NumFolders. */
	r = enc_uint64(a, numFolders);
	if (r < 0)
		return (r);

	/* Write External. */
	r = enc_uint64(a, 0);
	if (r < 0)
		return (r);

	for (fi = 0; fi < numFolders; fi++) {
		/* Write NumCoders. */
		r = enc_uint64(a, num_coder);
		if (r < 0)
			return (r);

		for (i = 0; i < num_coder; i++) {
			unsigned codec_id = coders[i].codec;

			/* Write Codec flag. */
			archive_be64enc(codec_buff, codec_id);
			for (codec_size = 8; codec_size > 0; codec_size--) {
				if (codec_buff[8 - codec_size])
					break;
			}
			if (codec_size == 0)
				codec_size = 1;
			if (coders[i].prop_size)
				r = enc_uint64(a, codec_size | 0x20);
			else
				r = enc_uint64(a, codec_size);
			if (r < 0)
				return (r);

			/* Write Codec ID. */
			codec_size &= 0x0f;
			r = (int)compress_out(a, &codec_buff[8-codec_size],
				codec_size, ARCHIVE_Z_RUN);
			if (r < 0)
				return (r);

			if (coders[i].prop_size) {
				/* Write Codec property size. */
				r = enc_uint64(a, coders[i].prop_size);
				if (r < 0)
					return (r);

				/* Write Codec properties. */
				r = (int)compress_out(a, coders[i].props,
					coders[i].prop_size, ARCHIVE_Z_RUN);
				if (r < 0)
					return (r);
			}
		}
	}

	/*
	 * Make CodersUnPackSize.
	 */
	r = enc_uint64(a, kCodersUnPackSize);
	if (r < 0)
		return (r);

	if (numFolders > 1) {
		struct file *file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->size == 0)
				break;
			r = enc_uint64(a, file->size);
			if (r < 0)
				return (r);
		}

	} else {
		/* Write UnPackSize. */
		r = enc_uint64(a, unpack_size);
		if (r < 0)
			return (r);
	}

	if (!substrm) {
		uint8_t crc[4];
		/*
		 * Make CRC.
		 */
		r = enc_uint64(a, kCRC);
		if (r < 0)
			return (r);

		/* All are defined */
		r = enc_uint64(a, 1);
		if (r < 0)
			return (r);
		archive_le32enc(crc, header_crc);
		r = (int)compress_out(a, crc, 4, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}

	/* Write End. */
	r = enc_uint64(a, kEnd);
	if (r < 0)
		return (r);

	if (substrm) {
		/*
		 * Make SubStreamsInfo.
		 */
		r = make_substreamsInfo(a, coders);
		if (r < 0)
			return (r);
	}


	/* Write End. */
	r = enc_uint64(a, kEnd);
	if (r < 0)
		return (r);

	return (ARCHIVE_OK);
}