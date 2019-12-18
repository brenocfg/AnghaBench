#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct archive_string_conv {scalar_t__ cd_w; scalar_t__ cd; int flag; unsigned int from_cp; } ;
struct TYPE_4__ {char const* s; size_t length; } ;
struct archive_mstring {void* aes_set; TYPE_1__ aes_mbs; int /*<<< orphan*/  aes_wcs; TYPE_1__ aes_utf8; } ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 void* AES_SET_MBS ; 
 void* AES_SET_UTF8 ; 
 void* AES_SET_WCS ; 
 unsigned int CP_UTF8 ; 
 int SCONV_FROM_UTF16 ; 
 int SCONV_NORMALIZATION_C ; 
 int SCONV_TO_UTF16 ; 
 int /*<<< orphan*/ * archive_string_append (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_1__*) ; 
 int archive_strncpy_l (TYPE_1__*,char const*,size_t,struct archive_string_conv*) ; 
 int archive_wstring_append_from_mbs_in_codepage (int /*<<< orphan*/ *,char const*,size_t,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_wstring_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbsnbytes (char const*,size_t) ; 

int
archive_mstring_copy_mbs_len_l(struct archive_mstring *aes,
    const char *mbs, size_t len, struct archive_string_conv *sc)
{
	int r;

	if (mbs == NULL) {
		aes->aes_set = 0;
		return (0);
	}
	archive_string_empty(&(aes->aes_mbs));
	archive_wstring_empty(&(aes->aes_wcs));
	archive_string_empty(&(aes->aes_utf8));
#if defined(_WIN32) && !defined(__CYGWIN__)
	/*
	 * Internationalization programming on Windows must use Wide
	 * characters because Windows platform cannot make locale UTF-8.
	 */
	if (sc == NULL) {
		if (archive_string_append(&(aes->aes_mbs),
			mbs, mbsnbytes(mbs, len)) == NULL) {
			aes->aes_set = 0;
			r = -1;
		} else {
			aes->aes_set = AES_SET_MBS;
			r = 0;
		}
#if defined(HAVE_ICONV)
	} else if (sc != NULL && sc->cd_w != (iconv_t)-1) {
		/*
		 * This case happens only when MultiByteToWideChar() cannot
		 * handle sc->from_cp, and we have to iconv in order to
		 * translate character-set to wchar_t,UTF-16.
		 */
		iconv_t cd = sc->cd;
		unsigned from_cp;
		int flag;

		/*
		 * Translate multi-bytes from some character-set to UTF-8.
		 */ 
		sc->cd = sc->cd_w;
		r = archive_strncpy_l(&(aes->aes_utf8), mbs, len, sc);
		sc->cd = cd;
		if (r != 0) {
			aes->aes_set = 0;
			return (r);
		}
		aes->aes_set = AES_SET_UTF8;

		/*
		 * Append the UTF-8 string into wstring.
		 */ 
		flag = sc->flag;
		sc->flag &= ~(SCONV_NORMALIZATION_C
				| SCONV_TO_UTF16| SCONV_FROM_UTF16);
		from_cp = sc->from_cp;
		sc->from_cp = CP_UTF8;
		r = archive_wstring_append_from_mbs_in_codepage(&(aes->aes_wcs),
			aes->aes_utf8.s, aes->aes_utf8.length, sc);
		sc->flag = flag;
		sc->from_cp = from_cp;
		if (r == 0)
			aes->aes_set |= AES_SET_WCS;
#endif
	} else {
		r = archive_wstring_append_from_mbs_in_codepage(
		    &(aes->aes_wcs), mbs, len, sc);
		if (r == 0)
			aes->aes_set = AES_SET_WCS;
		else
			aes->aes_set = 0;
	}
#else
	r = archive_strncpy_l(&(aes->aes_mbs), mbs, len, sc);
	if (r == 0)
		aes->aes_set = AES_SET_MBS; /* Only MBS form is set now. */
	else
		aes->aes_set = 0;
#endif
	return (r);
}