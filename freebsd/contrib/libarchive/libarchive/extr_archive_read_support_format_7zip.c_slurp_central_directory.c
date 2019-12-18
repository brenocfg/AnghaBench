#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct TYPE_6__ {TYPE_2__* folders; } ;
struct TYPE_8__ {TYPE_1__ ci; } ;
struct _7zip {scalar_t__ header_crc32; int header_is_encoded; int header_is_being_read; scalar_t__ pack_stream_bytes_unconsumed; scalar_t__ uncompressed_buffer_bytes_remaining; scalar_t__ folder_outbytes_remaining; scalar_t__ pack_stream_index; scalar_t__ pack_stream_remaining; TYPE_3__ si; scalar_t__ header_bytes_remaining; scalar_t__ has_encrypted_entries; scalar_t__ header_offset; scalar_t__ stream_offset; scalar_t__ seek_base; } ;
struct _7z_header_info {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {scalar_t__ digest; int /*<<< orphan*/  digest_defined; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* _7ZIP_SIGNATURE ; 
 unsigned char* __archive_read_ahead (struct archive_read*,int,scalar_t__*) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 scalar_t__ __archive_read_seek (struct archive_read*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_le32dec (unsigned char const*) ; 
 scalar_t__ archive_le64dec (unsigned char const*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*,...) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int decode_encoded_header_info (struct archive_read*,TYPE_3__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free_StreamsInfo (TYPE_3__*) ; 
 unsigned char* header_bytes (struct archive_read*,int) ; 
#define  kEncodedHeader 129 
 unsigned char const kEnd ; 
#define  kHeader 128 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int read_Header (struct archive_read*,struct _7z_header_info*,int) ; 
 int /*<<< orphan*/  read_consume (struct archive_read*) ; 
 int seek_pack (struct archive_read*) ; 
 int setup_decode_folder (struct archive_read*,TYPE_2__*,int) ; 
 int skip_sfx (struct archive_read*,scalar_t__) ; 

__attribute__((used)) static int
slurp_central_directory(struct archive_read *a, struct _7zip *zip,
    struct _7z_header_info *header)
{
	const unsigned char *p;
	uint64_t next_header_offset;
	uint64_t next_header_size;
	uint32_t next_header_crc;
	ssize_t bytes_avail;
	int check_header_crc, r;

	if ((p = __archive_read_ahead(a, 32, &bytes_avail)) == NULL)
		return (ARCHIVE_FATAL);

	if ((p[0] == 'M' && p[1] == 'Z') || memcmp(p, "\x7F\x45LF", 4) == 0) {
		/* This is an executable ? Must be self-extracting... */
		r = skip_sfx(a, bytes_avail);
		if (r < ARCHIVE_WARN)
			return (r);
		if ((p = __archive_read_ahead(a, 32, &bytes_avail)) == NULL)
			return (ARCHIVE_FATAL);
	}
	zip->seek_base += 32;

	if (memcmp(p, _7ZIP_SIGNATURE, 6) != 0) {
		archive_set_error(&a->archive, -1, "Not 7-Zip archive file");
		return (ARCHIVE_FATAL);
	}

	/* CRC check. */
	if (crc32(0, (const unsigned char *)p + 12, 20)
	    != archive_le32dec(p + 8)) {
		archive_set_error(&a->archive, -1, "Header CRC error");
		return (ARCHIVE_FATAL);
	}

	next_header_offset = archive_le64dec(p + 12);
	next_header_size = archive_le64dec(p + 20);
	next_header_crc = archive_le32dec(p + 28);

	if (next_header_size == 0)
		/* There is no entry in an archive file. */
		return (ARCHIVE_EOF);

	if (((int64_t)next_header_offset) < 0) {
		archive_set_error(&a->archive, -1, "Malformed 7-Zip archive");
		return (ARCHIVE_FATAL);
	}
	__archive_read_consume(a, 32);
	if (next_header_offset != 0) {
		if (bytes_avail >= (ssize_t)next_header_offset)
			__archive_read_consume(a, next_header_offset);
		else if (__archive_read_seek(a,
		    next_header_offset + zip->seek_base, SEEK_SET) < 0)
			return (ARCHIVE_FATAL);
	}
	zip->stream_offset = next_header_offset;
	zip->header_offset = next_header_offset;
	zip->header_bytes_remaining = next_header_size;
	zip->header_crc32 = 0;
	zip->header_is_encoded = 0;
	zip->header_is_being_read = 1;
	zip->has_encrypted_entries = 0;
	check_header_crc = 1;

	if ((p = header_bytes(a, 1)) == NULL) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated 7-Zip file body");
		return (ARCHIVE_FATAL);
	}
	/* Parse ArchiveProperties. */
	switch (p[0]) {
	case kEncodedHeader:
		/*
		 * The archive has an encoded header and we have to decode it
		 * in order to parse the header correctly.
		 */
		r = decode_encoded_header_info(a, &(zip->si));

		/* Check the EncodedHeader CRC.*/
		if (r == 0 && zip->header_crc32 != next_header_crc) {
			archive_set_error(&a->archive, -1,
			    "Damaged 7-Zip archive");
			r = -1;
		}
		if (r == 0) {
			if (zip->si.ci.folders[0].digest_defined)
				next_header_crc = zip->si.ci.folders[0].digest;
			else
				check_header_crc = 0;
			if (zip->pack_stream_bytes_unconsumed)
				read_consume(a);
			r = setup_decode_folder(a, zip->si.ci.folders, 1);
			if (r == 0) {
				zip->header_bytes_remaining =
					zip->folder_outbytes_remaining;
				r = seek_pack(a);
			}
		}
		/* Clean up StreamsInfo. */
		free_StreamsInfo(&(zip->si));
		memset(&(zip->si), 0, sizeof(zip->si));
		if (r < 0)
			return (ARCHIVE_FATAL);
		zip->header_is_encoded = 1;
		zip->header_crc32 = 0;
		/* FALL THROUGH */
	case kHeader:
		/*
		 * Parse the header.
		 */
		errno = 0;
		r = read_Header(a, header, zip->header_is_encoded);
		if (r < 0) {
			if (errno == ENOMEM)
				archive_set_error(&a->archive, -1,
				    "Couldn't allocate memory");
			else
				archive_set_error(&a->archive, -1,
				    "Damaged 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/*
		 *  Must be kEnd.
		 */
		if ((p = header_bytes(a, 1)) == NULL ||*p != kEnd) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/* Check the Header CRC.*/
		if (check_header_crc && zip->header_crc32 != next_header_crc) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		break;
	default:
		archive_set_error(&a->archive, -1,
		    "Unexpected Property ID = %X", p[0]);
		return (ARCHIVE_FATAL);
	}

	/* Clean up variables be used for decoding the archive header */
	zip->pack_stream_remaining = 0;
	zip->pack_stream_index = 0;
	zip->folder_outbytes_remaining = 0;
	zip->uncompressed_buffer_bytes_remaining = 0;
	zip->pack_stream_bytes_unconsumed = 0;
	zip->header_is_being_read = 0;

	return (ARCHIVE_OK);
}