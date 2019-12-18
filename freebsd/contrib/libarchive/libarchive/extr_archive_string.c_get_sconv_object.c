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
struct archive_string_conv {scalar_t__ nconverter; } ;
struct archive {unsigned int current_codepage; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int SCONV_TO_CHARSET ; 
 int /*<<< orphan*/  add_sconv_object (struct archive*,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  canonical_charset_name (char const*) ; 
 struct archive_string_conv* create_sconv_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 struct archive_string_conv* find_sconv_object (struct archive*,char const*,char const*) ; 
 int /*<<< orphan*/  free_sconv_object (struct archive_string_conv*) ; 
 unsigned int get_current_codepage () ; 

__attribute__((used)) static struct archive_string_conv *
get_sconv_object(struct archive *a, const char *fc, const char *tc, int flag)
{
	struct archive_string_conv *sc;
	unsigned current_codepage;

	/* Check if we have made the sconv object. */
	sc = find_sconv_object(a, fc, tc);
	if (sc != NULL)
		return (sc);

	if (a == NULL)
		current_codepage = get_current_codepage();
	else
		current_codepage = a->current_codepage;

	sc = create_sconv_object(canonical_charset_name(fc),
	    canonical_charset_name(tc), current_codepage, flag);
	if (sc == NULL) {
		if (a != NULL)
			archive_set_error(a, ENOMEM,
			    "Could not allocate memory for "
			    "a string conversion object");
		return (NULL);
	}

	/*
	 * If there is no converter for current string conversion object,
	 * we cannot handle this conversion.
	 */
	if (sc->nconverter == 0) {
		if (a != NULL) {
#if HAVE_ICONV
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "iconv_open failed : Cannot handle ``%s''",
			    (flag & SCONV_TO_CHARSET)?tc:fc);
#else
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "A character-set conversion not fully supported "
			    "on this platform");
#endif
		}
		/* Failed; free a sconv object. */
		free_sconv_object(sc);
		return (NULL);
	}

	/*
	 * Success!
	 */
	if (a != NULL)
		add_sconv_object(a, sc);
	return (sc);
}