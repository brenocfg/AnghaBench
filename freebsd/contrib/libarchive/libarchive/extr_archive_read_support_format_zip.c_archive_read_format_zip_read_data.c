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
struct zip {int has_encrypted_entries; int entry_uncompressed_bytes_read; scalar_t__ entry_crc32; scalar_t__ (* crc32func ) (scalar_t__,void const*,unsigned int) ;scalar_t__ entry_compressed_bytes_read; TYPE_3__* entry; int /*<<< orphan*/  ignore_crc32; int /*<<< orphan*/  hctx_valid; scalar_t__ end_of_entry; scalar_t__ init_decryption; scalar_t__ unconsumed; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  unsigned long intmax_t ;
typedef  int int64_t ;
struct TYPE_5__ {scalar_t__ vendor; } ;
struct TYPE_6__ {int mode; int zip_flags; int compression; scalar_t__ compressed_size; int uncompressed_size; scalar_t__ crc32; TYPE_2__ aes_extra; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ AES_VENDOR_AE_2 ; 
 int AE_IFMT ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int ARCHIVE_WARN ; 
 int UINT32_MAX ; 
 int WINZIP_AES_ENCRYPTION ; 
 int ZIP_STRONG_ENCRYPTED ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 unsigned long compression_name (unsigned long) ; 
 int init_WinZip_AES_decryption (struct archive_read*) ; 
 int init_traditional_PKWARE_decryption (struct archive_read*) ; 
 int read_decryption_header (struct archive_read*) ; 
 scalar_t__ stub1 (scalar_t__,void const*,unsigned int) ; 
 int zip_read_data_deflate (struct archive_read*,void const**,size_t*,int*) ; 
 int zip_read_data_none (struct archive_read*,void const**,size_t*,int*) ; 
 int zip_read_data_zipx_bzip2 (struct archive_read*,void const**,size_t*,int*) ; 
 int zip_read_data_zipx_lzma_alone (struct archive_read*,void const**,size_t*,int*) ; 
 int zip_read_data_zipx_ppmd (struct archive_read*,void const**,size_t*,int*) ; 
 int zip_read_data_zipx_xz (struct archive_read*,void const**,size_t*,int*) ; 

__attribute__((used)) static int
archive_read_format_zip_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	int r;
	struct zip *zip = (struct zip *)(a->format->data);

	if (zip->has_encrypted_entries ==
			ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
		zip->has_encrypted_entries = 0;
	}

	*offset = zip->entry_uncompressed_bytes_read;
	*size = 0;
	*buff = NULL;

	/* If we hit end-of-entry last time, return ARCHIVE_EOF. */
	if (zip->end_of_entry)
		return (ARCHIVE_EOF);

	/* Return EOF immediately if this is a non-regular file. */
	if (AE_IFREG != (zip->entry->mode & AE_IFMT))
		return (ARCHIVE_EOF);

	__archive_read_consume(a, zip->unconsumed);
	zip->unconsumed = 0;

	if (zip->init_decryption) {
		zip->has_encrypted_entries = 1;
		if (zip->entry->zip_flags & ZIP_STRONG_ENCRYPTED)
			r = read_decryption_header(a);
		else if (zip->entry->compression == WINZIP_AES_ENCRYPTION)
			r = init_WinZip_AES_decryption(a);
		else
			r = init_traditional_PKWARE_decryption(a);
		if (r != ARCHIVE_OK)
			return (r);
		zip->init_decryption = 0;
	}

	switch(zip->entry->compression) {
	case 0:  /* No compression. */
		r =  zip_read_data_none(a, buff, size, offset);
		break;
#ifdef HAVE_BZLIB_H
	case 12: /* ZIPx bzip2 compression. */
		r = zip_read_data_zipx_bzip2(a, buff, size, offset);
		break;
#endif
#if HAVE_LZMA_H && HAVE_LIBLZMA
	case 14: /* ZIPx LZMA compression. */
		r = zip_read_data_zipx_lzma_alone(a, buff, size, offset);
		break;
	case 95: /* ZIPx XZ compression. */
		r = zip_read_data_zipx_xz(a, buff, size, offset);
		break;
#endif
	/* PPMd support is built-in, so we don't need any #if guards. */
	case 98: /* ZIPx PPMd compression. */
		r = zip_read_data_zipx_ppmd(a, buff, size, offset);
		break;

#ifdef HAVE_ZLIB_H
	case 8: /* Deflate compression. */
		r =  zip_read_data_deflate(a, buff, size, offset);
		break;
#endif
	default: /* Unsupported compression. */
		/* Return a warning. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported ZIP compression method (%d: %s)",
		    zip->entry->compression, compression_name(zip->entry->compression));
		/* We can't decompress this entry, but we will
		 * be able to skip() it and try the next entry. */
		return (ARCHIVE_FAILED);
		break;
	}
	if (r != ARCHIVE_OK)
		return (r);
	/* Update checksum */
	if (*size)
		zip->entry_crc32 = zip->crc32func(zip->entry_crc32, *buff,
		    (unsigned)*size);
	/* If we hit the end, swallow any end-of-data marker. */
	if (zip->end_of_entry) {
		/* Check file size, CRC against these values. */
		if (zip->entry->compressed_size !=
		    zip->entry_compressed_bytes_read) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP compressed data is wrong size "
			    "(read %jd, expected %jd)",
			    (intmax_t)zip->entry_compressed_bytes_read,
			    (intmax_t)zip->entry->compressed_size);
			return (ARCHIVE_WARN);
		}
		/* Size field only stores the lower 32 bits of the actual
		 * size. */
		if ((zip->entry->uncompressed_size & UINT32_MAX)
		    != (zip->entry_uncompressed_bytes_read & UINT32_MAX)) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP uncompressed data is wrong size "
			    "(read %jd, expected %jd)\n",
			    (intmax_t)zip->entry_uncompressed_bytes_read,
			    (intmax_t)zip->entry->uncompressed_size);
			return (ARCHIVE_WARN);
		}
		/* Check computed CRC against header */
		if ((!zip->hctx_valid ||
		      zip->entry->aes_extra.vendor != AES_VENDOR_AE_2) &&
		   zip->entry->crc32 != zip->entry_crc32
		    && !zip->ignore_crc32) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP bad CRC: 0x%lx should be 0x%lx",
			    (unsigned long)zip->entry_crc32,
			    (unsigned long)zip->entry->crc32);
			return (ARCHIVE_WARN);
		}
	}

	return (ARCHIVE_OK);
}