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
typedef  int /*<<< orphan*/  wchar_t ;
struct archive_string_conv {int dummy; } ;
struct archive_string {char const* s; } ;
struct archive_mstring {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  nfd ;
typedef  int /*<<< orphan*/  nfc ;
typedef  int /*<<< orphan*/  mstr ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  LC_ALL ; 
 int SCONV_SET_OPT_NORMALIZATION_D ; 
 int /*<<< orphan*/  archive_mstring_clean (struct archive_mstring*) ; 
 int /*<<< orphan*/  archive_mstring_copy_mbs_len_l (struct archive_mstring*,char*,int,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_mstring_copy_wcs (struct archive_mstring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_mstring_get_mbs_l (struct archive_mstring*,char const**,size_t*,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_mstring_get_wcs (struct archive*,struct archive_mstring*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_strcpy_l (struct archive_string*,char*,struct archive_string_conv*) ; 
 struct archive_string_conv* archive_string_conversion_from_charset (struct archive*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_conversion_set_opt (struct archive_string_conv*,int) ; 
 struct archive_string_conv* archive_string_conversion_to_charset (struct archive*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  archive_strncpy_l (struct archive_string*,char*,int,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualUTF8String (char*,char const*) ; 
 int /*<<< orphan*/  assertEqualWString (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  failure (char*,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int is_wc_unicode () ; 
 int /*<<< orphan*/  memset (struct archive_mstring*,int /*<<< orphan*/ ,int) ; 
 int scan_unicode_pattern (char*,int /*<<< orphan*/ *,char*,char*,char*,int) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skipping (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
test_archive_string_normalization_mac_nfd(const char *testdata)
{
	struct archive *a, *a2;
	struct archive_string utf8;
	struct archive_mstring mstr;
	struct archive_string_conv *f_sconv8, *t_sconv8;
	struct archive_string_conv *f_sconv16be, *f_sconv16le;
	FILE *fp;
	char buff[512];
	int line = 0;
	int locale_is_utf8, wc_is_unicode;
	int sconv_opt = SCONV_SET_OPT_NORMALIZATION_D;

	locale_is_utf8 = (NULL != setlocale(LC_ALL, "en_US.UTF-8"));
	wc_is_unicode = is_wc_unicode();
	/* If it doesn't exist, just warn and return. */
	if (!locale_is_utf8 && !wc_is_unicode) {
		skipping("A test of string normalization for NFD requires "
		    "a suitable locale; en_US.UTF-8 not available on this "
		    "system");
		return;
	}

	archive_string_init(&utf8);
	memset(&mstr, 0, sizeof(mstr));

	/*
	 * Create string conversion objects.
	 */
	assert((a = archive_read_new()) != NULL);
	assertA(NULL != (f_sconv8 =
	    archive_string_conversion_from_charset(a, "UTF-8", 0)));
	assertA(NULL != (f_sconv16be =
	    archive_string_conversion_from_charset(a, "UTF-16BE", 0)));
	assertA(NULL != (f_sconv16le =
	    archive_string_conversion_from_charset(a, "UTF-16LE", 0)));
	assert((a2 = archive_write_new()) != NULL);
	assertA(NULL != (t_sconv8 =
	    archive_string_conversion_to_charset(a2, "UTF-8", 0)));
	if (f_sconv8 == NULL || f_sconv16be == NULL || f_sconv16le == NULL ||
	    t_sconv8 == NULL) {
		/* We cannot continue this test. */
		assertEqualInt(ARCHIVE_OK, archive_read_free(a));
		return;
	}
	archive_string_conversion_set_opt(f_sconv8, sconv_opt);
	archive_string_conversion_set_opt(f_sconv16be, sconv_opt);
	archive_string_conversion_set_opt(f_sconv16le, sconv_opt);
	archive_string_conversion_set_opt(t_sconv8, sconv_opt);

	/* Open a test pattern file. */
	assert((fp = fopen(testdata, "r")) != NULL);

	/*
	 * Read test data.
	 *  Test data format:
	 *     <NFC Unicode pattern> ';' <NFD Unicode pattern> '\n'
	 *  Unicode pattern format:
	 *     [0-9A-F]{4,5}([ ][0-9A-F]{4,5}){0,}
	 */
	while (fgets(buff, sizeof(buff), fp) != NULL) {
		char nfc[80], nfd[80];
		char utf8_nfc[80], utf8_nfd[80];
		char utf16be_nfc[80], utf16be_nfd[80];
		char utf16le_nfc[80], utf16le_nfd[80];
		wchar_t wc_nfc[40], wc_nfd[40];
		char *e, *p;
		const wchar_t *wp;
		const char *mp;
		size_t mplen;
		int should_be_nfc;

		line++;
		if (buff[0] == '#')
			continue;
		p = strchr(buff, ';');
		if (p == NULL)
			continue;
		*p++ = '\0';
		/* Copy an NFC pattern */
		strncpy(nfc, buff, sizeof(nfc)-1);
		nfc[sizeof(nfc)-1] = '\0';
		e = p;
		p = strchr(p, '\n');
		if (p == NULL)
			continue;
		*p = '\0';
		/* Copy an NFD pattern */
		strncpy(nfd, e, sizeof(nfd)-1);
		nfd[sizeof(nfd)-1] = '\0';

		/*
		 * Get an NFC patterns.
		 */
		should_be_nfc = scan_unicode_pattern(utf8_nfc, wc_nfc,
			utf16be_nfc, utf16le_nfc, nfc, 1);

		/*
		 * Get an NFD patterns.
		 */
		scan_unicode_pattern(utf8_nfd, wc_nfd, utf16be_nfd, utf16le_nfd,
		    nfd, 0);

		if (locale_is_utf8) {
			/*
			 * Normalize an NFC string for import.
			 */
			assertEqualInt(0, archive_strcpy_l(
			    &utf8, utf8_nfc, f_sconv8));
			if (should_be_nfc) {
				failure("NFC(%s) should not be converted to"
				    " NFD(%s):%d", nfc, nfd, line);
				assertEqualUTF8String(utf8_nfc, utf8.s);
			} else {
				failure("NFC(%s) should be converted to"
				    " NFD(%s):%d", nfc, nfd, line);
				assertEqualUTF8String(utf8_nfd, utf8.s);
			}

			/*
			 * Normalize an NFD string for import.
			 */
			assertEqualInt(0, archive_strcpy_l(
			    &utf8, utf8_nfd, f_sconv8));
			failure("NFD(%s) should not be any changed:%d",
			    nfd, line);
			assertEqualUTF8String(utf8_nfd, utf8.s);

			/*
			 * Copy an NFD string for export.
			 */
			assertEqualInt(0, archive_strcpy_l(
			    &utf8, utf8_nfd, t_sconv8));
			failure("NFD(%s) should not be any changed:%d",
			    nfd, line);
			assertEqualUTF8String(utf8_nfd, utf8.s);

			/*
			 * Normalize an NFC string in UTF-16BE for import.
			 */
			assertEqualInt(0, archive_strncpy_l(
			    &utf8, utf16be_nfc, 100000, f_sconv16be));
			if (should_be_nfc) {
				failure("NFC(%s) should not be converted to"
				    " NFD(%s):%d", nfc, nfd, line);
				assertEqualUTF8String(utf8_nfc, utf8.s);
			} else {
				failure("NFC(%s) should be converted to"
				    " NFD(%s):%d", nfc, nfd, line);
				assertEqualUTF8String(utf8_nfd, utf8.s);
			}

			/*
			 * Normalize an NFC string in UTF-16LE for import.
			 */
			assertEqualInt(0, archive_strncpy_l(
			    &utf8, utf16le_nfc, 100000, f_sconv16le));
			if (should_be_nfc) {
				failure("NFC(%s) should not be converted to"
				    " NFD(%s):%d", nfc, nfd, line);
				assertEqualUTF8String(utf8_nfc, utf8.s);
			} else {
				failure("NFC(%s) should be converted to"
				    " NFD(%s):%d", nfc, nfd, line);
				assertEqualUTF8String(utf8_nfd, utf8.s);
			}
		}

		/*
		 * Test for archive_mstring interface.
		 * In specific, Windows platform UTF-16BE is directly
		 * converted to/from wide-character to avoid the effect of
		 * current locale since windows platform cannot make
		 * locale UTF-8.
		 */
		if (locale_is_utf8 || wc_is_unicode) {
			/*
			 * Normalize an NFD string in UTF-8 for import.
			 */
			assertEqualInt(0, archive_mstring_copy_mbs_len_l(
			    &mstr, utf8_nfc, 100000, f_sconv8));
			assertEqualInt(0,
			    archive_mstring_get_wcs(a, &mstr, &wp));
			if (should_be_nfc) {
				failure("UTF-8 NFC(%s) should not be converted "
				    "to WCS NFD(%s):%d", nfc, nfd, line);
				assertEqualWString(wc_nfc, wp);
			} else {
				failure("UTF-8 NFC(%s) should be converted "
				    "to WCS NFD(%s):%d", nfc, nfd, line);
				assertEqualWString(wc_nfd, wp);
			}

			/*
			 * Normalize an NFD string in UTF-16BE for import.
			 */
			assertEqualInt(0, archive_mstring_copy_mbs_len_l(
			    &mstr, utf16be_nfc, 100000, f_sconv16be));
			assertEqualInt(0,
			    archive_mstring_get_wcs(a, &mstr, &wp));
			if (should_be_nfc) {
				failure("UTF-16BE NFC(%s) should not be "
				    "converted to WCS NFD(%s):%d",
				    nfc, nfd, line);
				assertEqualWString(wc_nfc, wp);
			} else {
				failure("UTF-16BE NFC(%s) should be converted "
				    "to WCS NFD(%s):%d", nfc, nfd, line);
				assertEqualWString(wc_nfd, wp);
			}

			/*
			 * Normalize an NFD string in UTF-16LE for import.
			 */
			assertEqualInt(0, archive_mstring_copy_mbs_len_l(
			    &mstr, utf16le_nfc, 100000, f_sconv16le));
			assertEqualInt(0,
			    archive_mstring_get_wcs(a, &mstr, &wp));
			if (should_be_nfc) {
				failure("UTF-16LE NFC(%s) should not be "
				    "converted to WCS NFD(%s):%d",
				    nfc, nfd, line);
				assertEqualWString(wc_nfc, wp);
			} else {
				failure("UTF-16LE NFC(%s) should be converted "
				    "to WCS NFD(%s):%d", nfc, nfd, line);
				assertEqualWString(wc_nfd, wp);
			}

			/*
			 * Copy an NFD wide-string for export.
			 */
			assertEqualInt(0, archive_mstring_copy_wcs(
			    &mstr, wc_nfd));
			assertEqualInt(0, archive_mstring_get_mbs_l(
			    &mstr, &mp, &mplen, t_sconv8));
			failure("WCS NFD(%s) should be UTF-8 NFD:%d"
			    ,nfd, line);
			assertEqualUTF8String(utf8_nfd, mp);
		}
	}

	archive_string_free(&utf8);
	archive_mstring_clean(&mstr);
	fclose(fp);
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a2));
}