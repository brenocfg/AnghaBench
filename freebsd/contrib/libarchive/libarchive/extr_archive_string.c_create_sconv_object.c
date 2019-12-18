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
struct archive_string_conv {unsigned int from_cp; unsigned int to_cp; int same; scalar_t__ cd_w; scalar_t__ cd; int flag; int /*<<< orphan*/  utftmp; struct archive_string_conv* from_charset; int /*<<< orphan*/ * to_charset; int /*<<< orphan*/ * next; } ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 scalar_t__ CP_UTF16BE ; 
 scalar_t__ CP_UTF16LE ; 
 scalar_t__ CP_UTF8 ; 
 scalar_t__ IsValidCodePage (unsigned int) ; 
 int SCONV_BEST_EFFORT ; 
 int SCONV_FROM_CHARSET ; 
 int SCONV_FROM_UTF16 ; 
 int SCONV_FROM_UTF16BE ; 
 int SCONV_FROM_UTF16LE ; 
 int SCONV_FROM_UTF8 ; 
 int SCONV_NORMALIZATION_C ; 
 int SCONV_NORMALIZATION_D ; 
 int SCONV_TO_CHARSET ; 
 int SCONV_TO_UTF16 ; 
 int SCONV_TO_UTF16BE ; 
 int SCONV_TO_UTF16LE ; 
 int SCONV_TO_UTF8 ; 
 int SCONV_WIN_CP ; 
 int /*<<< orphan*/  archive_string_init (int /*<<< orphan*/ *) ; 
 struct archive_string_conv* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct archive_string_conv*) ; 
 void* iconv_open (char const*,char const*) ; 
 void* make_codepage_from_charset (char const*) ; 
 int /*<<< orphan*/  setup_converter (struct archive_string_conv*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static struct archive_string_conv *
create_sconv_object(const char *fc, const char *tc,
    unsigned current_codepage, int flag)
{
	struct archive_string_conv *sc; 

	sc = calloc(1, sizeof(*sc));
	if (sc == NULL)
		return (NULL);
	sc->next = NULL;
	sc->from_charset = strdup(fc);
	if (sc->from_charset == NULL) {
		free(sc);
		return (NULL);
	}
	sc->to_charset = strdup(tc);
	if (sc->to_charset == NULL) {
		free(sc->from_charset);
		free(sc);
		return (NULL);
	}
	archive_string_init(&sc->utftmp);

	if (flag & SCONV_TO_CHARSET) {
		/*
		 * Convert characters from the current locale charset to
		 * a specified charset.
		 */
		sc->from_cp = current_codepage;
		sc->to_cp = make_codepage_from_charset(tc);
#if defined(_WIN32) && !defined(__CYGWIN__)
		if (IsValidCodePage(sc->to_cp))
			flag |= SCONV_WIN_CP;
#endif
	} else if (flag & SCONV_FROM_CHARSET) {
		/*
		 * Convert characters from a specified charset to
		 * the current locale charset.
		 */
		sc->to_cp = current_codepage;
		sc->from_cp = make_codepage_from_charset(fc);
#if defined(_WIN32) && !defined(__CYGWIN__)
		if (IsValidCodePage(sc->from_cp))
			flag |= SCONV_WIN_CP;
#endif
	}

	/*
	 * Check if "from charset" and "to charset" are the same.
	 */
	if (strcmp(fc, tc) == 0 ||
	    (sc->from_cp != (unsigned)-1 && sc->from_cp == sc->to_cp))
		sc->same = 1;
	else
		sc->same = 0;

	/*
	 * Mark if "from charset" or "to charset" are UTF-8 or UTF-16BE/LE.
	 */
	if (strcmp(tc, "UTF-8") == 0)
		flag |= SCONV_TO_UTF8;
	else if (strcmp(tc, "UTF-16BE") == 0)
		flag |= SCONV_TO_UTF16BE;
	else if (strcmp(tc, "UTF-16LE") == 0)
		flag |= SCONV_TO_UTF16LE;
	if (strcmp(fc, "UTF-8") == 0)
		flag |= SCONV_FROM_UTF8;
	else if (strcmp(fc, "UTF-16BE") == 0)
		flag |= SCONV_FROM_UTF16BE;
	else if (strcmp(fc, "UTF-16LE") == 0)
		flag |= SCONV_FROM_UTF16LE;
#if defined(_WIN32) && !defined(__CYGWIN__)
	if (sc->to_cp == CP_UTF8)
		flag |= SCONV_TO_UTF8;
	else if (sc->to_cp == CP_UTF16BE)
		flag |= SCONV_TO_UTF16BE | SCONV_WIN_CP;
	else if (sc->to_cp == CP_UTF16LE)
		flag |= SCONV_TO_UTF16LE | SCONV_WIN_CP;
	if (sc->from_cp == CP_UTF8)
		flag |= SCONV_FROM_UTF8;
	else if (sc->from_cp == CP_UTF16BE)
		flag |= SCONV_FROM_UTF16BE | SCONV_WIN_CP;
	else if (sc->from_cp == CP_UTF16LE)
		flag |= SCONV_FROM_UTF16LE | SCONV_WIN_CP;
#endif

	/*
	 * Set a flag for Unicode NFD. Usually iconv cannot correctly
	 * handle it. So we have to translate NFD characters to NFC ones
	 * ourselves before iconv handles. Another reason is to prevent
	 * that the same sight of two filenames, one is NFC and other
	 * is NFD, would be in its directory.
	 * On Mac OS X, although its filesystem layer automatically
	 * convert filenames to NFD, it would be useful for filename
	 * comparing to find out the same filenames that we normalize
	 * that to be NFD ourselves.
	 */
	if ((flag & SCONV_FROM_CHARSET) &&
	    (flag & (SCONV_FROM_UTF16 | SCONV_FROM_UTF8))) {
#if defined(__APPLE__)
		if (flag & SCONV_TO_UTF8)
			flag |= SCONV_NORMALIZATION_D;
		else
#endif
			flag |= SCONV_NORMALIZATION_C;
	}
#if defined(__APPLE__)
	/*
	 * In case writing an archive file, make sure that a filename
	 * going to be passed to iconv is a Unicode NFC string since
	 * a filename in HFS Plus filesystem is a Unicode NFD one and
	 * iconv cannot handle it with "UTF-8" charset. It is simpler
	 * than a use of "UTF-8-MAC" charset.
	 */
	if ((flag & SCONV_TO_CHARSET) &&
	    (flag & (SCONV_FROM_UTF16 | SCONV_FROM_UTF8)) &&
	    !(flag & (SCONV_TO_UTF16 | SCONV_TO_UTF8)))
		flag |= SCONV_NORMALIZATION_C;
	/*
	 * In case reading an archive file. make sure that a filename
	 * will be passed to users is a Unicode NFD string in order to
	 * correctly compare the filename with other one which comes
	 * from HFS Plus filesystem.
	 */
	if ((flag & SCONV_FROM_CHARSET) &&
	   !(flag & (SCONV_FROM_UTF16 | SCONV_FROM_UTF8)) &&
	    (flag & SCONV_TO_UTF8))
		flag |= SCONV_NORMALIZATION_D;
#endif

#if defined(HAVE_ICONV)
	sc->cd_w = (iconv_t)-1;
	/*
	 * Create an iconv object.
	 */
	if (((flag & (SCONV_TO_UTF8 | SCONV_TO_UTF16)) &&
	    (flag & (SCONV_FROM_UTF8 | SCONV_FROM_UTF16))) ||
	    (flag & SCONV_WIN_CP)) {
		/* This case we won't use iconv. */
		sc->cd = (iconv_t)-1;
	} else {
		sc->cd = iconv_open(tc, fc);
		if (sc->cd == (iconv_t)-1 && (sc->flag & SCONV_BEST_EFFORT)) {
			/*
			 * Unfortunately, all of iconv implements do support
			 * "CP932" character-set, so we should use "SJIS"
			 * instead if iconv_open failed.
			 */
			if (strcmp(tc, "CP932") == 0)
				sc->cd = iconv_open("SJIS", fc);
			else if (strcmp(fc, "CP932") == 0)
				sc->cd = iconv_open(tc, "SJIS");
		}
#if defined(_WIN32) && !defined(__CYGWIN__)
		/*
		 * archive_mstring on Windows directly convert multi-bytes
		 * into archive_wstring in order not to depend on locale
		 * so that you can do a I18N programming. This will be
		 * used only in archive_mstring_copy_mbs_len_l so far.
		 */
		if (flag & SCONV_FROM_CHARSET) {
			sc->cd_w = iconv_open("UTF-8", fc);
			if (sc->cd_w == (iconv_t)-1 &&
			    (sc->flag & SCONV_BEST_EFFORT)) {
				if (strcmp(fc, "CP932") == 0)
					sc->cd_w = iconv_open("UTF-8", "SJIS");
			}
		}
#endif /* _WIN32 && !__CYGWIN__ */
	}
#endif	/* HAVE_ICONV */

	sc->flag = flag;

	/*
	 * Set up converters.
	 */
	setup_converter(sc);

	return (sc);
}