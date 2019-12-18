#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct _7zip {char opt_compression_level; int /*<<< orphan*/  opt_compression; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  _7Z_BZIP2 ; 
 int /*<<< orphan*/  _7Z_COPY ; 
 int /*<<< orphan*/  _7Z_DEFLATE ; 
 int /*<<< orphan*/  _7Z_LZMA1 ; 
 int /*<<< orphan*/  _7Z_LZMA2 ; 
 int /*<<< orphan*/  _7Z_PPMD ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
_7z_options(struct archive_write *a, const char *key, const char *value)
{
	struct _7zip *zip;

	zip = (struct _7zip *)a->format_data;

	if (strcmp(key, "compression") == 0) {
		const char *name = NULL;

		if (value == NULL || strcmp(value, "copy") == 0 ||
		    strcmp(value, "COPY") == 0 ||
		    strcmp(value, "store") == 0 ||
		    strcmp(value, "STORE") == 0)
			zip->opt_compression = _7Z_COPY;
		else if (strcmp(value, "deflate") == 0 ||
		    strcmp(value, "DEFLATE") == 0)
#if HAVE_ZLIB_H
			zip->opt_compression = _7Z_DEFLATE;
#else
			name = "deflate";
#endif
		else if (strcmp(value, "bzip2") == 0 ||
		    strcmp(value, "BZIP2") == 0)
#if defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR)
			zip->opt_compression = _7Z_BZIP2;
#else
			name = "bzip2";
#endif
		else if (strcmp(value, "lzma1") == 0 ||
		    strcmp(value, "LZMA1") == 0)
#if HAVE_LZMA_H
			zip->opt_compression = _7Z_LZMA1;
#else
			name = "lzma1";
#endif
		else if (strcmp(value, "lzma2") == 0 ||
		    strcmp(value, "LZMA2") == 0)
#if HAVE_LZMA_H
			zip->opt_compression = _7Z_LZMA2;
#else
			name = "lzma2";
#endif
		else if (strcmp(value, "ppmd") == 0 ||
		    strcmp(value, "PPMD") == 0 ||
		    strcmp(value, "PPMd") == 0)
			zip->opt_compression = _7Z_PPMD;
		else {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Unknown compression name: `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}
		if (name != NULL) {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "`%s' compression not supported "
			    "on this platform",
			    name);
			return (ARCHIVE_FAILED);
		}
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "compression-level") == 0) {
		if (value == NULL ||
		    !(value[0] >= '0' && value[0] <= '9') ||
		    value[1] != '\0') {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Illegal value `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}
		zip->opt_compression_level = value[0] - '0';
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}