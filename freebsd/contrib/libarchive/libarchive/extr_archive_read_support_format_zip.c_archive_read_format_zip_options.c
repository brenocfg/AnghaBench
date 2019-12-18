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
struct zip {int init_default_conversion; int ignore_crc32; int process_mac_extensions; int /*<<< orphan*/  crc32func; int /*<<< orphan*/ * sconv; int /*<<< orphan*/ * sconv_utf8; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * archive_string_conversion_from_charset (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fake_crc32 ; 
 int /*<<< orphan*/  real_crc32 ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
archive_read_format_zip_options(struct archive_read *a,
    const char *key, const char *val)
{
	struct zip *zip;
	int ret = ARCHIVE_FAILED;

	zip = (struct zip *)(a->format->data);
	if (strcmp(key, "compat-2x")  == 0) {
		/* Handle filenames as libarchive 2.x */
		zip->init_default_conversion = (val != NULL) ? 1 : 0;
		return (ARCHIVE_OK);
	} else if (strcmp(key, "hdrcharset")  == 0) {
		if (val == NULL || val[0] == 0)
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "zip: hdrcharset option needs a character-set name"
			);
		else {
			zip->sconv = archive_string_conversion_from_charset(
			    &a->archive, val, 0);
			if (zip->sconv != NULL) {
				if (strcmp(val, "UTF-8") == 0)
					zip->sconv_utf8 = zip->sconv;
				ret = ARCHIVE_OK;
			} else
				ret = ARCHIVE_FATAL;
		}
		return (ret);
	} else if (strcmp(key, "ignorecrc32") == 0) {
		/* Mostly useful for testing. */
		if (val == NULL || val[0] == 0) {
			zip->crc32func = real_crc32;
			zip->ignore_crc32 = 0;
		} else {
			zip->crc32func = fake_crc32;
			zip->ignore_crc32 = 1;
		}
		return (ARCHIVE_OK);
	} else if (strcmp(key, "mac-ext") == 0) {
		zip->process_mac_extensions = (val != NULL && val[0] != 0);
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}