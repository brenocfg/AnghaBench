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
struct archive_string_conv {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_string_conversion_charset_name (struct archive_string_conv*) ; 
 struct archive_string_conv* archive_string_conversion_to_charset (struct archive*,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
test_archive_string_canonicalization(void)
{
	struct archive *a;
	struct archive_string_conv *sconv;

	setlocale(LC_ALL, "en_US.UTF-8");

	assert((a = archive_read_new()) != NULL);

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "UTF-8", 1)));
	failure("Charset name should be UTF-8");
	assertEqualString("UTF-8",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "UTF8", 1)));
	failure("Charset name should be UTF-8");
	assertEqualString("UTF-8",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "utf8", 1)));
	failure("Charset name should be UTF-8");
	assertEqualString("UTF-8",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "UTF-16BE", 1)));
	failure("Charset name should be UTF-16BE");
	assertEqualString("UTF-16BE",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "UTF16BE", 1)));
	failure("Charset name should be UTF-16BE");
	assertEqualString("UTF-16BE",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "utf16be", 1)));
	failure("Charset name should be UTF-16BE");
	assertEqualString("UTF-16BE",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "UTF-16LE", 1)));
	failure("Charset name should be UTF-16LE");
	assertEqualString("UTF-16LE",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "UTF16LE", 1)));
	failure("Charset name should be UTF-16LE");
	assertEqualString("UTF-16LE",
	    archive_string_conversion_charset_name(sconv));

	assertA(NULL != (sconv =
	    archive_string_conversion_to_charset(a, "utf16le", 1)));
	failure("Charset name should be UTF-16LE");
	assertEqualString("UTF-16LE",
	    archive_string_conversion_charset_name(sconv));

	assertEqualInt(ARCHIVE_OK, archive_read_free(a));

}