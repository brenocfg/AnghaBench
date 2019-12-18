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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ uInt ;
struct TYPE_2__ {scalar_t__ avail_out; int /*<<< orphan*/  next_out; void* opaque; void* zfree; void* zalloc; } ;
struct zip {int flags; scalar_t__ written_bytes; scalar_t__ entry_offset; size_t entry_uncompressed_limit; size_t entry_compressed_size; size_t entry_uncompressed_size; int entry_flags; int entry_uses_zip64; int entry_crc32; int (* crc32func ) (int,unsigned char const*,size_t) ;int entry_encryption; int encryption_type; void* entry_compression; void* requested_compression; unsigned char trad_chkdat; unsigned char* file_header; int aes_vendor; int /*<<< orphan*/  deflate_compression_level; TYPE_1__ stream; scalar_t__ len_buf; int /*<<< orphan*/  buf; scalar_t__ entry_uncompressed_written; scalar_t__ entry_compressed_written; struct archive_entry* entry; int /*<<< orphan*/  central_directory_bytes; int /*<<< orphan*/  file_header_extra_offset; int /*<<< orphan*/  central_directory_entries; struct archive_string_conv* opt_sconv; scalar_t__ hctx_valid; scalar_t__ cctx_valid; scalar_t__ tctx_valid; int /*<<< orphan*/  hctx; int /*<<< orphan*/  cctx; } ;
struct archive_write {int /*<<< orphan*/  archive; struct zip* format_data; } ;
struct archive_string_conv {int dummy; } ;
struct archive_entry {int dummy; } ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  local_header ;
typedef  int /*<<< orphan*/  local_extra ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int AES_VENDOR_AE_1 ; 
 int AES_VENDOR_AE_2 ; 
 scalar_t__ AE_IFDIR ; 
 scalar_t__ AE_IFLNK ; 
 scalar_t__ AE_IFREG ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 scalar_t__ ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ AUTH_CODE_SIZE ; 
 int /*<<< orphan*/  CODESET ; 
 void* COMPRESSION_DEFAULT ; 
 int COMPRESSION_DEFLATE ; 
 void* COMPRESSION_STORE ; 
 void* COMPRESSION_UNSPECIFIED ; 
#define  ENCRYPTION_TRADITIONAL 130 
#define  ENCRYPTION_WINZIP_AES128 129 
#define  ENCRYPTION_WINZIP_AES256 128 
 scalar_t__ ENOMEM ; 
 size_t INT64_MAX ; 
 scalar_t__ TRAD_HEADER_SIZE ; 
 scalar_t__ WINZIP_AES128_HEADER_SIZE ; 
 scalar_t__ WINZIP_AES256_HEADER_SIZE ; 
 int WINZIP_AES_ENCRYPTION ; 
 scalar_t__ ZIP_4GB_MAX ; 
 scalar_t__ ZIP_4GB_MAX_UNCOMPRESSED ; 
 int ZIP_ENTRY_FLAG_ENCRYPTED ; 
 int ZIP_ENTRY_FLAG_LENGTH_AT_END ; 
 int ZIP_ENTRY_FLAG_UTF8_NAME ; 
 int ZIP_FLAG_AVOID_ZIP64 ; 
 int ZIP_FLAG_EXPERIMENT_xl ; 
 int ZIP_FLAG_FORCE_ZIP64 ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 void* Z_NULL ; 
 scalar_t__ Z_OK ; 
 int __archive_write_output (struct archive_write*,...) ; 
 struct archive_entry* __la_win_entry_in_posix_pathseparator (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_encrypto_aes_ctr_release (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_entry_atime (struct archive_entry*) ; 
 scalar_t__ archive_entry_atime_is_set (struct archive_entry*) ; 
 void* archive_entry_clone (struct archive_entry*) ; 
 scalar_t__ archive_entry_ctime (struct archive_entry*) ; 
 scalar_t__ archive_entry_ctime_is_set (struct archive_entry*) ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 scalar_t__ archive_entry_gid (struct archive_entry*) ; 
 scalar_t__ archive_entry_mode (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 scalar_t__ archive_entry_pathname_l (struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_entry_set_pathname (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_symlink (struct archive_entry*,char const*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 scalar_t__ archive_entry_size_is_set (struct archive_entry*) ; 
 char* archive_entry_symlink (struct archive_entry*) ; 
 scalar_t__ archive_entry_symlink_l (struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 scalar_t__ archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_hmac_sha1_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_le16enc (unsigned char*,int) ; 
 int /*<<< orphan*/  archive_le32enc (unsigned char*,int) ; 
 int /*<<< orphan*/  archive_le64enc (unsigned char*,size_t) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  archive_string_conversion_charset_name (struct archive_string_conv*) ; 
 void* cd_alloc (struct zip*,int) ; 
 int /*<<< orphan*/  copy_path (struct archive_entry*,unsigned char*) ; 
 scalar_t__ deflateInit2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int dos_time (scalar_t__) ; 
 scalar_t__ errno ; 
 struct archive_string_conv* get_sconv (struct archive_write*,struct zip*) ; 
 int /*<<< orphan*/  is_all_ascii (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 
 size_t path_length (struct archive_entry*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t strlen (char const*) ; 
 int stub1 (int,unsigned char const*,size_t) ; 
 int stub2 (int,unsigned char const*,size_t) ; 
 int write_path (struct archive_entry*,struct archive_write*) ; 

__attribute__((used)) static int
archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
{
	unsigned char local_header[32];
	unsigned char local_extra[144];
	struct zip *zip = a->format_data;
	unsigned char *e;
	unsigned char *cd_extra;
	size_t filename_length;
	const char *slink = NULL;
	size_t slink_size = 0;
	struct archive_string_conv *sconv = get_sconv(a, zip);
	int ret, ret2 = ARCHIVE_OK;
	mode_t type;
	int version_needed = 10;

	/* Ignore types of entries that we don't support. */
	type = archive_entry_filetype(entry);
	if (type != AE_IFREG && type != AE_IFDIR && type != AE_IFLNK) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Filetype not supported");
		return ARCHIVE_FAILED;
	};

	/* If we're not using Zip64, reject large files. */
	if (zip->flags & ZIP_FLAG_AVOID_ZIP64) {
		/* Reject entries over 4GB. */
		if (archive_entry_size_is_set(entry)
		    && (archive_entry_size(entry) > ZIP_4GB_MAX)) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Files > 4GB require Zip64 extensions");
			return ARCHIVE_FAILED;
		}
		/* Reject entries if archive is > 4GB. */
		if (zip->written_bytes > ZIP_4GB_MAX) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Archives > 4GB require Zip64 extensions");
			return ARCHIVE_FAILED;
		}
	}

	/* Only regular files can have size > 0. */
	if (type != AE_IFREG)
		archive_entry_set_size(entry, 0);


	/* Reset information from last entry. */
	zip->entry_offset = zip->written_bytes;
	zip->entry_uncompressed_limit = INT64_MAX;
	zip->entry_compressed_size = 0;
	zip->entry_uncompressed_size = 0;
	zip->entry_compressed_written = 0;
	zip->entry_uncompressed_written = 0;
	zip->entry_flags = 0;
	zip->entry_uses_zip64 = 0;
	zip->entry_crc32 = zip->crc32func(0, NULL, 0);
	zip->entry_encryption = 0;
	archive_entry_free(zip->entry);
	zip->entry = NULL;

	if (zip->cctx_valid)
		archive_encrypto_aes_ctr_release(&zip->cctx);
	if (zip->hctx_valid)
		archive_hmac_sha1_cleanup(&zip->hctx);
	zip->tctx_valid = zip->cctx_valid = zip->hctx_valid = 0;

	if (type == AE_IFREG
		    &&(!archive_entry_size_is_set(entry)
			|| archive_entry_size(entry) > 0)) {
		switch (zip->encryption_type) {
		case ENCRYPTION_TRADITIONAL:
		case ENCRYPTION_WINZIP_AES128:
		case ENCRYPTION_WINZIP_AES256:
			zip->entry_flags |= ZIP_ENTRY_FLAG_ENCRYPTED;
			zip->entry_encryption = zip->encryption_type;
			break;
		default:
			break;
		}
	}


#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Make sure the path separators in pathname, hardlink and symlink
	 * are all slash '/', not the Windows path separator '\'. */
	zip->entry = __la_win_entry_in_posix_pathseparator(entry);
	if (zip->entry == entry)
		zip->entry = archive_entry_clone(entry);
#else
	zip->entry = archive_entry_clone(entry);
#endif
	if (zip->entry == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip header data");
		return (ARCHIVE_FATAL);
	}

	if (sconv != NULL) {
		const char *p;
		size_t len;

		if (archive_entry_pathname_l(entry, &p, &len, sconv) != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Pathname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate Pathname '%s' to %s",
			    archive_entry_pathname(entry),
			    archive_string_conversion_charset_name(sconv));
			ret2 = ARCHIVE_WARN;
		}
		if (len > 0)
			archive_entry_set_pathname(zip->entry, p);

		/*
		 * There is no standard for symlink handling; we convert
		 * it using the same character-set translation that we use
		 * for filename.
		 */
		if (type == AE_IFLNK) {
			if (archive_entry_symlink_l(entry, &p, &len, sconv)) {
				if (errno == ENOMEM) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory "
					    " for Symlink");
					return (ARCHIVE_FATAL);
				}
				/* No error if we can't convert. */
			} else if (len > 0)
				archive_entry_set_symlink(zip->entry, p);
		}
	}

	/* If filename isn't ASCII and we can use UTF-8, set the UTF-8 flag. */
	if (!is_all_ascii(archive_entry_pathname(zip->entry))) {
		if (zip->opt_sconv != NULL) {
			if (strcmp(archive_string_conversion_charset_name(
					zip->opt_sconv), "UTF-8") == 0)
				zip->entry_flags |= ZIP_ENTRY_FLAG_UTF8_NAME;
#if HAVE_NL_LANGINFO
		} else if (strcmp(nl_langinfo(CODESET), "UTF-8") == 0) {
			zip->entry_flags |= ZIP_ENTRY_FLAG_UTF8_NAME;
#endif
		}
	}
	filename_length = path_length(zip->entry);

	/* Determine appropriate compression and size for this entry. */
	if (type == AE_IFLNK) {
		slink = archive_entry_symlink(zip->entry);
		if (slink != NULL)
			slink_size = strlen(slink);
		else
			slink_size = 0;
		zip->entry_uncompressed_limit = slink_size;
		zip->entry_compressed_size = slink_size;
		zip->entry_uncompressed_size = slink_size;
		zip->entry_crc32 = zip->crc32func(zip->entry_crc32,
		    (const unsigned char *)slink, slink_size);
		zip->entry_compression = COMPRESSION_STORE;
		version_needed = 20;
	} else if (type != AE_IFREG) {
		zip->entry_compression = COMPRESSION_STORE;
		zip->entry_uncompressed_limit = 0;
		version_needed = 20;
	} else if (archive_entry_size_is_set(zip->entry)) {
		int64_t size = archive_entry_size(zip->entry);
		int64_t additional_size = 0;

		zip->entry_uncompressed_limit = size;
		zip->entry_compression = zip->requested_compression;
		if (zip->entry_compression == COMPRESSION_UNSPECIFIED) {
			zip->entry_compression = COMPRESSION_DEFAULT;
		}
		if (zip->entry_compression == COMPRESSION_STORE) {
			zip->entry_compressed_size = size;
			zip->entry_uncompressed_size = size;
			version_needed = 10;
		} else {
			zip->entry_uncompressed_size = size;
			version_needed = 20;
		}

		if (zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED) {
			switch (zip->entry_encryption) {
			case ENCRYPTION_TRADITIONAL:
				additional_size = TRAD_HEADER_SIZE;
				version_needed = 20;
				break;
			case ENCRYPTION_WINZIP_AES128:
				additional_size = WINZIP_AES128_HEADER_SIZE
				    + AUTH_CODE_SIZE;
				version_needed = 20;
				break;
			case ENCRYPTION_WINZIP_AES256:
				additional_size = WINZIP_AES256_HEADER_SIZE
				    + AUTH_CODE_SIZE;
				version_needed = 20;
				break;
			default:
				break;
			}
			if (zip->entry_compression == COMPRESSION_STORE)
				zip->entry_compressed_size += additional_size;
		}

		/*
		 * Set Zip64 extension in any of the following cases
		 * (this was suggested by discussion on info-zip-dev
		 * mailing list):
		 *  = Zip64 is being forced by user
		 *  = File is over 4GiB uncompressed
		 *    (including encryption header, if any)
		 *  = File is close to 4GiB and is being compressed
		 *    (compression might make file larger)
		 */
		if ((zip->flags & ZIP_FLAG_FORCE_ZIP64)
		    || (zip->entry_uncompressed_size + additional_size > ZIP_4GB_MAX)
		    || (zip->entry_uncompressed_size > ZIP_4GB_MAX_UNCOMPRESSED
			&& zip->entry_compression != COMPRESSION_STORE)) {
			zip->entry_uses_zip64 = 1;
			version_needed = 45;
		}

		/* We may know the size, but never the CRC. */
		zip->entry_flags |= ZIP_ENTRY_FLAG_LENGTH_AT_END;
	} else {
		/* We don't know the size.  In this case, we prefer
		 * deflate (it has a clear end-of-data marker which
		 * makes length-at-end more reliable) and will
		 * enable Zip64 extensions unless we're told not to.
		 */
		zip->entry_compression = COMPRESSION_DEFAULT;
		zip->entry_flags |= ZIP_ENTRY_FLAG_LENGTH_AT_END;
		if ((zip->flags & ZIP_FLAG_AVOID_ZIP64) == 0) {
			zip->entry_uses_zip64 = 1;
			version_needed = 45;
		} else if (zip->entry_compression == COMPRESSION_STORE) {
			version_needed = 10;
		} else {
			version_needed = 20;
		}

		if (zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED) {
			switch (zip->entry_encryption) {
			case ENCRYPTION_TRADITIONAL:
			case ENCRYPTION_WINZIP_AES128:
			case ENCRYPTION_WINZIP_AES256:
				if (version_needed < 20)
					version_needed = 20;
				break;
			default:
				break;
			}
		}
	}

	/* Format the local header. */
	memset(local_header, 0, sizeof(local_header));
	memcpy(local_header, "PK\003\004", 4);
	archive_le16enc(local_header + 4, version_needed);
	archive_le16enc(local_header + 6, zip->entry_flags);
	if (zip->entry_encryption == ENCRYPTION_WINZIP_AES128
	    || zip->entry_encryption == ENCRYPTION_WINZIP_AES256)
		archive_le16enc(local_header + 8, WINZIP_AES_ENCRYPTION);
	else
		archive_le16enc(local_header + 8, zip->entry_compression);
	archive_le32enc(local_header + 10,
		dos_time(archive_entry_mtime(zip->entry)));
	archive_le32enc(local_header + 14, zip->entry_crc32);
	if (zip->entry_uses_zip64) {
		/* Zip64 data in the local header "must" include both
		 * compressed and uncompressed sizes AND those fields
		 * are included only if these are 0xffffffff;
		 * THEREFORE these must be set this way, even if we
		 * know one of them is smaller. */
		archive_le32enc(local_header + 18, ZIP_4GB_MAX);
		archive_le32enc(local_header + 22, ZIP_4GB_MAX);
	} else {
		archive_le32enc(local_header + 18, (uint32_t)zip->entry_compressed_size);
		archive_le32enc(local_header + 22, (uint32_t)zip->entry_uncompressed_size);
	}
	archive_le16enc(local_header + 26, (uint16_t)filename_length);

	if (zip->entry_encryption == ENCRYPTION_TRADITIONAL) {
		if (zip->entry_flags & ZIP_ENTRY_FLAG_LENGTH_AT_END)
			zip->trad_chkdat = local_header[11];
		else
			zip->trad_chkdat = local_header[17];
	}

	/* Format as much of central directory file header as we can: */
	zip->file_header = cd_alloc(zip, 46);
	/* If (zip->file_header == NULL) XXXX */
	++zip->central_directory_entries;
	memset(zip->file_header, 0, 46);
	memcpy(zip->file_header, "PK\001\002", 4);
	/* "Made by PKZip 2.0 on Unix." */
	archive_le16enc(zip->file_header + 4, 3 * 256 + version_needed);
	archive_le16enc(zip->file_header + 6, version_needed);
	archive_le16enc(zip->file_header + 8, zip->entry_flags);
	if (zip->entry_encryption == ENCRYPTION_WINZIP_AES128
	    || zip->entry_encryption == ENCRYPTION_WINZIP_AES256)
		archive_le16enc(zip->file_header + 10, WINZIP_AES_ENCRYPTION);
	else
		archive_le16enc(zip->file_header + 10, zip->entry_compression);
	archive_le32enc(zip->file_header + 12,
		dos_time(archive_entry_mtime(zip->entry)));
	archive_le16enc(zip->file_header + 28, (uint16_t)filename_length);
	/* Following Info-Zip, store mode in the "external attributes" field. */
	archive_le32enc(zip->file_header + 38,
	    ((uint32_t)archive_entry_mode(zip->entry)) << 16);
	e = cd_alloc(zip, filename_length);
	/* If (e == NULL) XXXX */
	copy_path(zip->entry, e);

	/* Format extra data. */
	memset(local_extra, 0, sizeof(local_extra));
	e = local_extra;

	/* First, extra blocks that are the same between
	 * the local file header and the central directory.
	 * We format them once and then duplicate them. */

	/* UT timestamp, length depends on what timestamps are set. */
	memcpy(e, "UT", 2);
	archive_le16enc(e + 2,
	    1
	    + (archive_entry_mtime_is_set(entry) ? 4 : 0)
	    + (archive_entry_atime_is_set(entry) ? 4 : 0)
	    + (archive_entry_ctime_is_set(entry) ? 4 : 0));
	e += 4;
	*e++ =
	    (archive_entry_mtime_is_set(entry) ? 1 : 0)
	    | (archive_entry_atime_is_set(entry) ? 2 : 0)
	    | (archive_entry_ctime_is_set(entry) ? 4 : 0);
	if (archive_entry_mtime_is_set(entry)) {
		archive_le32enc(e, (uint32_t)archive_entry_mtime(entry));
		e += 4;
	}
	if (archive_entry_atime_is_set(entry)) {
		archive_le32enc(e, (uint32_t)archive_entry_atime(entry));
		e += 4;
	}
	if (archive_entry_ctime_is_set(entry)) {
		archive_le32enc(e, (uint32_t)archive_entry_ctime(entry));
		e += 4;
	}

	/* ux Unix extra data, length 11, version 1 */
	/* TODO: If uid < 64k, use 2 bytes, ditto for gid. */
	memcpy(e, "ux\013\000\001", 5);
	e += 5;
	*e++ = 4; /* Length of following UID */
	archive_le32enc(e, (uint32_t)archive_entry_uid(entry));
	e += 4;
	*e++ = 4; /* Length of following GID */
	archive_le32enc(e, (uint32_t)archive_entry_gid(entry));
	e += 4;

	/* AES extra data field: WinZIP AES information, ID=0x9901 */
	if ((zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED)
	    && (zip->entry_encryption == ENCRYPTION_WINZIP_AES128
	        || zip->entry_encryption == ENCRYPTION_WINZIP_AES256)) {

		memcpy(e, "\001\231\007\000\001\000AE", 8);
		/* AES vendor version AE-2 does not store a CRC.
		 * WinZip 11 uses AE-1, which does store the CRC,
		 * but it does not store the CRC when the file size
		 * is less than 20 bytes. So we simulate what
		 * WinZip 11 does.
		 * NOTE: WinZip 9.0 and 10.0 uses AE-2 by default. */
		if (archive_entry_size_is_set(zip->entry)
		    && archive_entry_size(zip->entry) < 20) {
			archive_le16enc(e+4, AES_VENDOR_AE_2);
			zip->aes_vendor = AES_VENDOR_AE_2;/* no CRC. */
		} else
			zip->aes_vendor = AES_VENDOR_AE_1;
		e += 8;
		/* AES encryption strength. */
		*e++ = (zip->entry_encryption == ENCRYPTION_WINZIP_AES128)?1:3;
		/* Actual compression method. */
		archive_le16enc(e, zip->entry_compression);
		e += 2;
	}

	/* Copy UT ,ux, and AES-extra into central directory as well. */
	zip->file_header_extra_offset = zip->central_directory_bytes;
	cd_extra = cd_alloc(zip, e - local_extra);
	memcpy(cd_extra, local_extra, e - local_extra);

	/*
	 * Following extra blocks vary between local header and
	 * central directory. These are the local header versions.
	 * Central directory versions get formatted in
	 * archive_write_zip_finish_entry() below.
	 */

	/* "[Zip64 entry] in the local header MUST include BOTH
	 * original [uncompressed] and compressed size fields." */
	if (zip->entry_uses_zip64) {
		unsigned char *zip64_start = e;
		memcpy(e, "\001\000\020\000", 4);
		e += 4;
		archive_le64enc(e, zip->entry_uncompressed_size);
		e += 8;
		archive_le64enc(e, zip->entry_compressed_size);
		e += 8;
		archive_le16enc(zip64_start + 2, (uint16_t)(e - (zip64_start + 4)));
	}

	if (zip->flags & ZIP_FLAG_EXPERIMENT_xl) {
		/* Experimental 'xl' extension to improve streaming. */
		unsigned char *external_info = e;
		int included = 7;
		memcpy(e, "xl\000\000", 4); // 0x6c65 + 2-byte length
		e += 4;
		e[0] = included; /* bitmap of included fields */
		e += 1;
		if (included & 1) {
			archive_le16enc(e, /* "Version created by" */
			    3 * 256 + version_needed);
			e += 2;
		}
		if (included & 2) {
			archive_le16enc(e, 0); /* internal file attributes */
			e += 2;
		}
		if (included & 4) {
			archive_le32enc(e,  /* external file attributes */
			    ((uint32_t)archive_entry_mode(zip->entry)) << 16);
			e += 4;
		}
		if (included & 8) {
			// Libarchive does not currently support file comments.
		}
		archive_le16enc(external_info + 2, (uint16_t)(e - (external_info + 4)));
	}

	/* Update local header with size of extra data and write it all out: */
	archive_le16enc(local_header + 28, (uint16_t)(e - local_extra));

	ret = __archive_write_output(a, local_header, 30);
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += 30;

	ret = write_path(zip->entry, a);
	if (ret <= ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += ret;

	ret = __archive_write_output(a, local_extra, e - local_extra);
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += e - local_extra;

	/* For symlinks, write the body now. */
	if (slink != NULL) {
		ret = __archive_write_output(a, slink, slink_size);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		zip->entry_compressed_written += slink_size;
		zip->entry_uncompressed_written += slink_size;
		zip->written_bytes += slink_size;
	}

#ifdef HAVE_ZLIB_H
	if (zip->entry_compression == COMPRESSION_DEFLATE) {
		zip->stream.zalloc = Z_NULL;
		zip->stream.zfree = Z_NULL;
		zip->stream.opaque = Z_NULL;
		zip->stream.next_out = zip->buf;
		zip->stream.avail_out = (uInt)zip->len_buf;
		if (deflateInit2(&zip->stream, zip->deflate_compression_level,
		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't init deflate compressor");
			return (ARCHIVE_FATAL);
		}
	}
#endif

	return (ret2);
}