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
struct archive_string_conv {int flag; scalar_t__ cd; scalar_t__ nconverter; scalar_t__ same; } ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int SCONV_BEST_EFFORT ; 
 int SCONV_FROM_CHARSET ; 
 int SCONV_FROM_UTF16 ; 
 int SCONV_FROM_UTF16BE ; 
 int SCONV_FROM_UTF16LE ; 
 int SCONV_FROM_UTF8 ; 
 int SCONV_NORMALIZATION_C ; 
 int SCONV_NORMALIZATION_D ; 
 int SCONV_TO_UTF16 ; 
 int SCONV_TO_UTF16BE ; 
 int SCONV_TO_UTF8 ; 
 int SCONV_UTF8_LIBARCHIVE_2 ; 
 int SCONV_WIN_CP ; 
 int /*<<< orphan*/  add_converter (struct archive_string_conv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_append_unicode ; 
 int /*<<< orphan*/  archive_string_normalize_C ; 
 int /*<<< orphan*/  archive_string_normalize_D ; 
 int /*<<< orphan*/  best_effort_strncat_from_utf16be ; 
 int /*<<< orphan*/  best_effort_strncat_from_utf16le ; 
 int /*<<< orphan*/  best_effort_strncat_in_locale ; 
 int /*<<< orphan*/  best_effort_strncat_to_utf16be ; 
 int /*<<< orphan*/  best_effort_strncat_to_utf16le ; 
 int /*<<< orphan*/  iconv_strncat_in_locale ; 
 int /*<<< orphan*/  strncat_from_utf8_libarchive2 ; 
 int /*<<< orphan*/  strncat_from_utf8_to_utf8 ; 
 int /*<<< orphan*/  strncat_in_codepage ; 
 int /*<<< orphan*/  win_strncat_from_utf16be ; 
 int /*<<< orphan*/  win_strncat_from_utf16le ; 
 int /*<<< orphan*/  win_strncat_to_utf16be ; 
 int /*<<< orphan*/  win_strncat_to_utf16le ; 

__attribute__((used)) static void
setup_converter(struct archive_string_conv *sc)
{

	/* Reset. */
	sc->nconverter = 0;

	/*
	 * Perform special sequence for the incorrect UTF-8 filenames
	 * made by libarchive2.x.
	 */
	if (sc->flag & SCONV_UTF8_LIBARCHIVE_2) {
		add_converter(sc, strncat_from_utf8_libarchive2);
		return;
	}

	/*
	 * Convert a string to UTF-16BE/LE.
	 */
	if (sc->flag & SCONV_TO_UTF16) {
		/*
		 * If the current locale is UTF-8, we can translate
		 * a UTF-8 string into a UTF-16BE string.
		 */
		if (sc->flag & SCONV_FROM_UTF8) {
			add_converter(sc, archive_string_append_unicode);
			return;
		}

#if defined(_WIN32) && !defined(__CYGWIN__)
		if (sc->flag & SCONV_WIN_CP) {
			if (sc->flag & SCONV_TO_UTF16BE)
				add_converter(sc, win_strncat_to_utf16be);
			else
				add_converter(sc, win_strncat_to_utf16le);
			return;
		}
#endif

#if defined(HAVE_ICONV)
		if (sc->cd != (iconv_t)-1) {
			add_converter(sc, iconv_strncat_in_locale);
			return;
		}
#endif

		if (sc->flag & SCONV_BEST_EFFORT) {
			if (sc->flag & SCONV_TO_UTF16BE)
				add_converter(sc,
					best_effort_strncat_to_utf16be);
			else
				add_converter(sc,
					best_effort_strncat_to_utf16le);
		} else
			/* Make sure we have no converter. */
			sc->nconverter = 0;
		return;
	}

	/*
	 * Convert a string from UTF-16BE/LE.
	 */
	if (sc->flag & SCONV_FROM_UTF16) {
		/*
		 * At least we should normalize a UTF-16BE string.
		 */
		if (sc->flag & SCONV_NORMALIZATION_D)
			add_converter(sc,archive_string_normalize_D);
		else if (sc->flag & SCONV_NORMALIZATION_C)
			add_converter(sc, archive_string_normalize_C);

		if (sc->flag & SCONV_TO_UTF8) {
			/*
			 * If the current locale is UTF-8, we can translate
			 * a UTF-16BE/LE string into a UTF-8 string directly.
			 */
			if (!(sc->flag &
			    (SCONV_NORMALIZATION_D |SCONV_NORMALIZATION_C)))
				add_converter(sc,
				    archive_string_append_unicode);
			return;
		}

#if defined(_WIN32) && !defined(__CYGWIN__)
		if (sc->flag & SCONV_WIN_CP) {
			if (sc->flag & SCONV_FROM_UTF16BE)
				add_converter(sc, win_strncat_from_utf16be);
			else
				add_converter(sc, win_strncat_from_utf16le);
			return;
		}
#endif

#if defined(HAVE_ICONV)
		if (sc->cd != (iconv_t)-1) {
			add_converter(sc, iconv_strncat_in_locale);
			return;
		}
#endif

		if ((sc->flag & (SCONV_BEST_EFFORT | SCONV_FROM_UTF16BE))
		    == (SCONV_BEST_EFFORT | SCONV_FROM_UTF16BE))
			add_converter(sc, best_effort_strncat_from_utf16be);
		else if ((sc->flag & (SCONV_BEST_EFFORT | SCONV_FROM_UTF16LE))
		    == (SCONV_BEST_EFFORT | SCONV_FROM_UTF16LE))
			add_converter(sc, best_effort_strncat_from_utf16le);
		else
			/* Make sure we have no converter. */
			sc->nconverter = 0;
		return;
	}

	if (sc->flag & SCONV_FROM_UTF8) {
		/*
		 * At least we should normalize a UTF-8 string.
		 */
		if (sc->flag & SCONV_NORMALIZATION_D)
			add_converter(sc,archive_string_normalize_D);
		else if (sc->flag & SCONV_NORMALIZATION_C)
			add_converter(sc, archive_string_normalize_C);

		/*
		 * Copy UTF-8 string with a check of CESU-8.
		 * Apparently, iconv does not check surrogate pairs in UTF-8
		 * when both from-charset and to-charset are UTF-8, and then
		 * we use our UTF-8 copy code.
		 */
		if (sc->flag & SCONV_TO_UTF8) {
			/*
			 * If the current locale is UTF-8, we can translate
			 * a UTF-16BE string into a UTF-8 string directly.
			 */
			if (!(sc->flag &
			    (SCONV_NORMALIZATION_D |SCONV_NORMALIZATION_C)))
				add_converter(sc, strncat_from_utf8_to_utf8);
			return;
		}
	}

#if defined(_WIN32) && !defined(__CYGWIN__)
	/*
	 * On Windows we can use Windows API for a string conversion.
	 */
	if (sc->flag & SCONV_WIN_CP) {
		add_converter(sc, strncat_in_codepage);
		return;
	}
#endif

#if HAVE_ICONV
	if (sc->cd != (iconv_t)-1) {
		add_converter(sc, iconv_strncat_in_locale);
		/*
		 * iconv generally does not support UTF-8-MAC and so
		 * we have to the output of iconv from NFC to NFD if
		 * need.
		 */
		if ((sc->flag & SCONV_FROM_CHARSET) &&
		    (sc->flag & SCONV_TO_UTF8)) {
			if (sc->flag & SCONV_NORMALIZATION_D)
				add_converter(sc, archive_string_normalize_D);
		}
		return;
	}
#endif

	/*
	 * Try conversion in the best effort or no conversion.
	 */
	if ((sc->flag & SCONV_BEST_EFFORT) || sc->same)
		add_converter(sc, best_effort_strncat_in_locale);
	else
		/* Make sure we have no converter. */
		sc->nconverter = 0;
}