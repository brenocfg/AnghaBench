#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct zip {scalar_t__ entry_crc32; int unconsumed; int end_of_entry; scalar_t__ entry_bytes_remaining; size_t decrypted_buffer_size; int entry_uncompressed_bytes_read; int entry_compressed_bytes_read; scalar_t__ decrypted_buffer; int /*<<< orphan*/  cctx; int /*<<< orphan*/  hctx; int /*<<< orphan*/  tctx; scalar_t__ tctx_valid; scalar_t__ cctx_valid; scalar_t__ hctx_valid; TYPE_3__* entry; scalar_t__ ignore_crc32; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {scalar_t__ vendor; } ;
struct TYPE_6__ {int zip_flags; int flags; scalar_t__ uncompressed_size; scalar_t__ compressed_size; scalar_t__ crc32; TYPE_2__ aes_extra; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ AES_VENDOR_AE_2 ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int AUTH_CODE_SIZE ; 
 scalar_t__ INT64_MAX ; 
 int LA_USED_ZIP64 ; 
 int ZIP_LENGTH_AT_END ; 
 char* __archive_read_ahead (struct archive_read*,int,int*) ; 
 int /*<<< orphan*/  archive_decrypto_aes_ctr_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  archive_hmac_sha1_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ archive_le32dec (char const*) ; 
 scalar_t__ archive_le64dec (char const*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int check_authentication_code (struct archive_read*,char const*) ; 
 int /*<<< orphan*/  trad_enc_decrypt_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,scalar_t__,size_t) ; 

__attribute__((used)) static int
zip_read_data_none(struct archive_read *a, const void **_buff,
    size_t *size, int64_t *offset)
{
	struct zip *zip;
	const char *buff;
	ssize_t bytes_avail;
	int r;

	(void)offset; /* UNUSED */

	zip = (struct zip *)(a->format->data);

	if (zip->entry->zip_flags & ZIP_LENGTH_AT_END) {
		const char *p;
		ssize_t grabbing_bytes = 24;

		if (zip->hctx_valid)
			grabbing_bytes += AUTH_CODE_SIZE;
		/* Grab at least 24 bytes. */
		buff = __archive_read_ahead(a, grabbing_bytes, &bytes_avail);
		if (bytes_avail < grabbing_bytes) {
			/* Zip archives have end-of-archive markers
			   that are longer than this, so a failure to get at
			   least 24 bytes really does indicate a truncated
			   file. */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated ZIP file data");
			return (ARCHIVE_FATAL);
		}
		/* Check for a complete PK\007\010 signature, followed
		 * by the correct 4-byte CRC. */
		p = buff;
		if (zip->hctx_valid)
			p += AUTH_CODE_SIZE;
		if (p[0] == 'P' && p[1] == 'K'
		    && p[2] == '\007' && p[3] == '\010'
		    && (archive_le32dec(p + 4) == zip->entry_crc32
			|| zip->ignore_crc32
			|| (zip->hctx_valid
			 && zip->entry->aes_extra.vendor == AES_VENDOR_AE_2))) {
			if (zip->entry->flags & LA_USED_ZIP64) {
				uint64_t compressed, uncompressed;
				zip->entry->crc32 = archive_le32dec(p + 4);
				compressed = archive_le64dec(p + 8);
				uncompressed = archive_le64dec(p + 16);
				if (compressed > INT64_MAX || uncompressed >
				    INT64_MAX) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_FILE_FORMAT,
					    "Overflow of 64-bit file sizes");
					return ARCHIVE_FAILED;
				}
				zip->entry->compressed_size = compressed;
				zip->entry->uncompressed_size = uncompressed;
				zip->unconsumed = 24;
			} else {
				zip->entry->crc32 = archive_le32dec(p + 4);
				zip->entry->compressed_size =
					archive_le32dec(p + 8);
				zip->entry->uncompressed_size =
					archive_le32dec(p + 12);
				zip->unconsumed = 16;
			}
			if (zip->hctx_valid) {
				r = check_authentication_code(a, buff);
				if (r != ARCHIVE_OK)
					return (r);
			}
			zip->end_of_entry = 1;
			return (ARCHIVE_OK);
		}
		/* If not at EOF, ensure we consume at least one byte. */
		++p;

		/* Scan forward until we see where a PK\007\010 signature
		 * might be. */
		/* Return bytes up until that point.  On the next call,
		 * the code above will verify the data descriptor. */
		while (p < buff + bytes_avail - 4) {
			if (p[3] == 'P') { p += 3; }
			else if (p[3] == 'K') { p += 2; }
			else if (p[3] == '\007') { p += 1; }
			else if (p[3] == '\010' && p[2] == '\007'
			    && p[1] == 'K' && p[0] == 'P') {
				if (zip->hctx_valid)
					p -= AUTH_CODE_SIZE;
				break;
			} else { p += 4; }
		}
		bytes_avail = p - buff;
	} else {
		if (zip->entry_bytes_remaining == 0) {
			zip->end_of_entry = 1;
			if (zip->hctx_valid) {
				r = check_authentication_code(a, NULL);
				if (r != ARCHIVE_OK)
					return (r);
			}
			return (ARCHIVE_OK);
		}
		/* Grab a bunch of bytes. */
		buff = __archive_read_ahead(a, 1, &bytes_avail);
		if (bytes_avail <= 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated ZIP file data");
			return (ARCHIVE_FATAL);
		}
		if (bytes_avail > zip->entry_bytes_remaining)
			bytes_avail = (ssize_t)zip->entry_bytes_remaining;
	}
	if (zip->tctx_valid || zip->cctx_valid) {
		size_t dec_size = bytes_avail;

		if (dec_size > zip->decrypted_buffer_size)
			dec_size = zip->decrypted_buffer_size;
		if (zip->tctx_valid) {
			trad_enc_decrypt_update(&zip->tctx,
			    (const uint8_t *)buff, dec_size,
			    zip->decrypted_buffer, dec_size);
		} else {
			size_t dsize = dec_size;
			archive_hmac_sha1_update(&zip->hctx,
			    (const uint8_t *)buff, dec_size);
			archive_decrypto_aes_ctr_update(&zip->cctx,
			    (const uint8_t *)buff, dec_size,
			    zip->decrypted_buffer, &dsize);
		}
		bytes_avail = dec_size;
		buff = (const char *)zip->decrypted_buffer;
	}
	*size = bytes_avail;
	zip->entry_bytes_remaining -= bytes_avail;
	zip->entry_uncompressed_bytes_read += bytes_avail;
	zip->entry_compressed_bytes_read += bytes_avail;
	zip->unconsumed += bytes_avail;
	*_buff = buff;
	return (ARCHIVE_OK);
}