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
struct archive_string {char const* s; } ;

/* Variables and functions */
 char const* ARCHIVE_VERSION_STRING ; 
 char* archive_bzlib_version () ; 
 char* archive_liblz4_version () ; 
 char* archive_liblzma_version () ; 
 char* archive_libzstd_version () ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char const*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  archive_strncat (struct archive_string*,char const*,int) ; 
 char* archive_zlib_version () ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

const char *
archive_version_details(void)
{
	static struct archive_string str;
	static int init = 0;
	const char *zlib = archive_zlib_version();
	const char *liblzma = archive_liblzma_version();
	const char *bzlib = archive_bzlib_version();
	const char *liblz4 = archive_liblz4_version();
	const char *libzstd = archive_libzstd_version();

	if (!init) {
		archive_string_init(&str);

		archive_strcat(&str, ARCHIVE_VERSION_STRING);
		if (zlib != NULL) {
			archive_strcat(&str, " zlib/");
			archive_strcat(&str, zlib);
		}
		if (liblzma) {
			archive_strcat(&str, " liblzma/");
			archive_strcat(&str, liblzma);
		}
		if (bzlib) {
			const char *p = bzlib;
			const char *sep = strchr(p, ',');
			if (sep == NULL)
				sep = p + strlen(p);
			archive_strcat(&str, " bz2lib/");
			archive_strncat(&str, p, sep - p);
		}
		if (liblz4) {
			archive_strcat(&str, " liblz4/");
			archive_strcat(&str, liblz4);
		}
		if (libzstd) {
			archive_strcat(&str, " libzstd/");
			archive_strcat(&str, libzstd);
		}
	}
	return str.s;
}