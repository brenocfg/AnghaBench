#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct archive_read {int /*<<< orphan*/  archive; int /*<<< orphan*/  entry; TYPE_2__* format; } ;
struct _7zip {unsigned char** sub_stream_buff; unsigned int pack_stream_remaining; unsigned int pack_stream_index; int folder_outbytes_remaining; int has_encrypted_entries; size_t main_stream_bytes_remaining; size_t pack_stream_bytes_unconsumed; int pack_stream_inbytes_remaining; size_t* sub_stream_size; size_t* sub_stream_bytes_remaining; int tmp_stream_buff_size; scalar_t__ uncompressed_buffer_bytes_remaining; scalar_t__ bcj2_outPos; scalar_t__ odd_bcj_size; scalar_t__ tmp_stream_bytes_remaining; scalar_t__ tmp_stream_bytes_avail; int /*<<< orphan*/ * tmp_stream_buff; } ;
struct _7z_folder {unsigned int numCoders; int numInStreams; int numOutStreams; int* unPackSize; scalar_t__ packIndex; struct _7z_coder* coders; TYPE_1__* bindPairs; scalar_t__ numPackedStreams; } ;
struct _7z_coder {int codec; int member_1; int member_2; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int inIndex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ _7Z_COPY ; 
#define  _7Z_CRYPTO_AES_256_SHA_256 131 
#define  _7Z_CRYPTO_MAIN_ZIP 130 
#define  _7Z_CRYPTO_RAR_29 129 
#define  _7Z_X86_BCJ2 128 
 int /*<<< orphan*/  archive_entry_set_is_data_encrypted (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_set_is_metadata_encrypted (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ extract_pack_stream (struct archive_read*,int /*<<< orphan*/ ) ; 
 void* folder_uncompressed_size (struct _7z_folder*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ get_uncompressed_data (struct archive_read*,void const**,scalar_t__,int /*<<< orphan*/ ) ; 
 int init_decompression (struct archive_read*,struct _7zip*,struct _7z_coder const*,struct _7z_coder const*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,scalar_t__) ; 
 int /*<<< orphan*/  read_consume (struct archive_read*) ; 
 int seek_pack (struct archive_read*) ; 

__attribute__((used)) static int
setup_decode_folder(struct archive_read *a, struct _7z_folder *folder,
    int header)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	const struct _7z_coder *coder1, *coder2;
	const char *cname = (header)?"archive header":"file content";
	unsigned i;
	int r, found_bcj2 = 0;

	/*
	 * Release the memory which the previous folder used for BCJ2.
	 */
	for (i = 0; i < 3; i++) {
		free(zip->sub_stream_buff[i]);
		zip->sub_stream_buff[i] = NULL;
	}

	/*
	 * Initialize a stream reader.
	 */
	zip->pack_stream_remaining = (unsigned)folder->numPackedStreams;
	zip->pack_stream_index = (unsigned)folder->packIndex;
	zip->folder_outbytes_remaining = folder_uncompressed_size(folder);
	zip->uncompressed_buffer_bytes_remaining = 0;

	/*
	 * Check coder types.
	 */
	for (i = 0; i < folder->numCoders; i++) {
		switch(folder->coders[i].codec) {
			case _7Z_CRYPTO_MAIN_ZIP:
			case _7Z_CRYPTO_RAR_29:
			case _7Z_CRYPTO_AES_256_SHA_256: {
				/* For entry that is associated with this folder, mark
				   it as encrypted (data+metadata). */
				zip->has_encrypted_entries = 1;
				if (a->entry) {
					archive_entry_set_is_data_encrypted(a->entry, 1);
					archive_entry_set_is_metadata_encrypted(a->entry, 1);
				}
				archive_set_error(&(a->archive),
					ARCHIVE_ERRNO_MISC,
					"The %s is encrypted, "
					"but currently not supported", cname);
				return (ARCHIVE_FATAL);
			}
			case _7Z_X86_BCJ2: {
				found_bcj2++;
				break;
			}
		}
	}
	/* Now that we've checked for encryption, if there were still no
	 * encrypted entries found we can say for sure that there are none.
	 */
	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
		zip->has_encrypted_entries = 0;
	}

	if ((folder->numCoders > 2 && !found_bcj2) || found_bcj2 > 1) {
		archive_set_error(&(a->archive),
		    ARCHIVE_ERRNO_MISC,
		    "The %s is encoded with many filters, "
		    "but currently not supported", cname);
		return (ARCHIVE_FATAL);
	}
	coder1 = &(folder->coders[0]);
	if (folder->numCoders == 2)
		coder2 = &(folder->coders[1]);
	else
		coder2 = NULL;

	if (found_bcj2) {
		/*
		 * Preparation to decode BCJ2.
		 * Decoding BCJ2 requires four sources. Those are at least,
		 * as far as I know, two types of the storage form.
		 */
		const struct _7z_coder *fc = folder->coders;
		static const struct _7z_coder coder_copy = {0, 1, 1, 0, NULL};
		const struct _7z_coder *scoder[3] =
			{&coder_copy, &coder_copy, &coder_copy};
		const void *buff;
		ssize_t bytes;
		unsigned char *b[3] = {NULL, NULL, NULL};
		uint64_t sunpack[3] ={-1, -1, -1};
		size_t s[3] = {0, 0, 0};
		int idx[3] = {0, 1, 2};

		if (folder->numCoders == 4 && fc[3].codec == _7Z_X86_BCJ2 &&
		    folder->numInStreams == 7 && folder->numOutStreams == 4 &&
		    zip->pack_stream_remaining == 4) {
			/* Source type 1 made by 7zr or 7z with -m options. */
			if (folder->bindPairs[0].inIndex == 5) {
				/* The form made by 7zr */
				idx[0] = 1; idx[1] = 2; idx[2] = 0;
				scoder[1] = &(fc[1]);
				scoder[2] = &(fc[0]);
				sunpack[1] = folder->unPackSize[1];
				sunpack[2] = folder->unPackSize[0];
				coder1 = &(fc[2]);
			} else {
				/*
				 * NOTE: Some patterns do not work.
				 * work:
				 *  7z a -m0=BCJ2 -m1=COPY -m2=COPY
				 *       -m3=(any)
				 *  7z a -m0=BCJ2 -m1=COPY -m2=(any)
				 *       -m3=COPY
				 *  7z a -m0=BCJ2 -m1=(any) -m2=COPY
				 *       -m3=COPY
				 * not work:
				 *  other patterns.
				 *
				 * We have to handle this like `pipe' or
				 * our libarchive7s filter frame work,
				 * decoding the BCJ2 main stream sequentially,
				 * m3 -> m2 -> m1 -> BCJ2.
				 *
				 */
				if (fc[0].codec == _7Z_COPY &&
				    fc[1].codec == _7Z_COPY)
					coder1 = &(folder->coders[2]);
				else if (fc[0].codec == _7Z_COPY &&
				    fc[2].codec == _7Z_COPY)
					coder1 = &(folder->coders[1]);
				else if (fc[1].codec == _7Z_COPY &&
				    fc[2].codec == _7Z_COPY)
					coder1 = &(folder->coders[0]);
				else {
					archive_set_error(&(a->archive),
					    ARCHIVE_ERRNO_MISC,
					    "Unsupported form of "
					    "BCJ2 streams");
					return (ARCHIVE_FATAL);
				}
			}
			coder2 = &(fc[3]);
			zip->main_stream_bytes_remaining =
				(size_t)folder->unPackSize[2];
		} else if (coder2 != NULL && coder2->codec == _7Z_X86_BCJ2 &&
		    zip->pack_stream_remaining == 4 &&
		    folder->numInStreams == 5 && folder->numOutStreams == 2) {
			/* Source type 0 made by 7z */
			zip->main_stream_bytes_remaining =
				(size_t)folder->unPackSize[0];
		} else {
			/* We got an unexpected form. */
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Unsupported form of BCJ2 streams");
			return (ARCHIVE_FATAL);
		}

		/* Skip the main stream at this time. */
		if ((r = seek_pack(a)) < 0)
			return (r);
		zip->pack_stream_bytes_unconsumed =
		    (size_t)zip->pack_stream_inbytes_remaining;
		read_consume(a);

		/* Read following three sub streams. */
		for (i = 0; i < 3; i++) {
			const struct _7z_coder *coder = scoder[i];

			if ((r = seek_pack(a)) < 0) {
				free(b[0]); free(b[1]); free(b[2]);
				return (r);
			}

			if (sunpack[i] == (uint64_t)-1)
				zip->folder_outbytes_remaining =
				    zip->pack_stream_inbytes_remaining;
			else
				zip->folder_outbytes_remaining = sunpack[i];

			r = init_decompression(a, zip, coder, NULL);
			if (r != ARCHIVE_OK) {
				free(b[0]); free(b[1]); free(b[2]);
				return (ARCHIVE_FATAL);
			}

			/* Allocate memory for the decoded data of a sub
			 * stream. */
			b[i] = malloc((size_t)zip->folder_outbytes_remaining);
			if (b[i] == NULL) {
				free(b[0]); free(b[1]); free(b[2]);
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for 7-Zip decompression");
				return (ARCHIVE_FATAL);
			}

			/* Extract a sub stream. */
			while (zip->pack_stream_inbytes_remaining > 0) {
				r = (int)extract_pack_stream(a, 0);
				if (r < 0) {
					free(b[0]); free(b[1]); free(b[2]);
					return (r);
				}
				bytes = get_uncompressed_data(a, &buff,
				    zip->uncompressed_buffer_bytes_remaining,
				    0);
				if (bytes < 0) {
					free(b[0]); free(b[1]); free(b[2]);
					return ((int)bytes);
				}
				memcpy(b[i]+s[i], buff, bytes);
				s[i] += bytes;
				if (zip->pack_stream_bytes_unconsumed)
					read_consume(a);
			}
		}

		/* Set the sub streams to the right place. */
		for (i = 0; i < 3; i++) {
			zip->sub_stream_buff[i] = b[idx[i]];
			zip->sub_stream_size[i] = s[idx[i]];
			zip->sub_stream_bytes_remaining[i] = s[idx[i]];
		}

		/* Allocate memory used for decoded main stream bytes. */
		if (zip->tmp_stream_buff == NULL) {
			zip->tmp_stream_buff_size = 32 * 1024;
			zip->tmp_stream_buff =
			    malloc(zip->tmp_stream_buff_size);
			if (zip->tmp_stream_buff == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for 7-Zip decompression");
				return (ARCHIVE_FATAL);
			}
		}
		zip->tmp_stream_bytes_avail = 0;
		zip->tmp_stream_bytes_remaining = 0;
		zip->odd_bcj_size = 0;
		zip->bcj2_outPos = 0;

		/*
		 * Reset a stream reader in order to read the main stream
		 * of BCJ2.
		 */
		zip->pack_stream_remaining = 1;
		zip->pack_stream_index = (unsigned)folder->packIndex;
		zip->folder_outbytes_remaining =
		    folder_uncompressed_size(folder);
		zip->uncompressed_buffer_bytes_remaining = 0;
	}

	/*
	 * Initialize the decompressor for the new folder's pack streams.
	 */
	r = init_decompression(a, zip, coder1, coder2);
	if (r != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	return (ARCHIVE_OK);
}