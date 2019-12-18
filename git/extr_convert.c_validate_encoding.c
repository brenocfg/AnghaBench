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

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  advise (char const*,char const*,char const*,...) ; 
 int /*<<< orphan*/  die (char const*,char const*,char const*) ; 
 int error (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ has_prohibited_utf_bom (char const*,char const*,size_t) ; 
 scalar_t__ is_missing_required_utf_bom (char const*,char const*,size_t) ; 
 scalar_t__ istarts_with (char const*,char*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int strlen (char*) ; 
 char* xstrdup_toupper (char const*) ; 

__attribute__((used)) static int validate_encoding(const char *path, const char *enc,
		      const char *data, size_t len, int die_on_error)
{
	/* We only check for UTF here as UTF?? can be an alias for UTF-?? */
	if (istarts_with(enc, "UTF")) {
		/*
		 * Check for detectable errors in UTF encodings
		 */
		if (has_prohibited_utf_bom(enc, data, len)) {
			const char *error_msg = _(
				"BOM is prohibited in '%s' if encoded as %s");
			/*
			 * This advice is shown for UTF-??BE and UTF-??LE encodings.
			 * We cut off the last two characters of the encoding name
			 * to generate the encoding name suitable for BOMs.
			 */
			const char *advise_msg = _(
				"The file '%s' contains a byte order "
				"mark (BOM). Please use UTF-%s as "
				"working-tree-encoding.");
			const char *stripped = NULL;
			char *upper = xstrdup_toupper(enc);
			upper[strlen(upper)-2] = '\0';
			if (skip_prefix(upper, "UTF", &stripped))
				skip_prefix(stripped, "-", &stripped);
			advise(advise_msg, path, stripped);
			free(upper);
			if (die_on_error)
				die(error_msg, path, enc);
			else {
				return error(error_msg, path, enc);
			}

		} else if (is_missing_required_utf_bom(enc, data, len)) {
			const char *error_msg = _(
				"BOM is required in '%s' if encoded as %s");
			const char *advise_msg = _(
				"The file '%s' is missing a byte order "
				"mark (BOM). Please use UTF-%sBE or UTF-%sLE "
				"(depending on the byte order) as "
				"working-tree-encoding.");
			const char *stripped = NULL;
			char *upper = xstrdup_toupper(enc);
			if (skip_prefix(upper, "UTF", &stripped))
				skip_prefix(stripped, "-", &stripped);
			advise(advise_msg, path, stripped, stripped);
			free(upper);
			if (die_on_error)
				die(error_msg, path, enc);
			else {
				return error(error_msg, path, enc);
			}
		}

	}
	return 0;
}