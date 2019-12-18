#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ mnemonic_t ;
struct TYPE_8__ {scalar_t__ chlen; int* ch; } ;
typedef  TYPE_2__ _VIQRState ;
struct TYPE_9__ {TYPE_1__* mroot; } ;
typedef  TYPE_3__ _VIQREncodingInfo ;

/* Variables and functions */
 int E2BIG ; 
 int EILSEQ ; 
 int EINVAL ; 
 int ESCAPE ; 
 int /*<<< orphan*/  memcpy (char*,int*,scalar_t__) ; 
 int /*<<< orphan*/ * mnemonic_ext ; 
 char* mnemonic_ext_find (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnemonic_ext_size ; 
 TYPE_1__* mnemonic_list_find (int /*<<< orphan*/ *,int) ; 
 char** mnemonic_rfc1456 ; 

__attribute__((used)) static int
_citrus_VIQR_wcrtomb_priv(_VIQREncodingInfo * __restrict ei,
    char * __restrict s, size_t n, wchar_t wc,
    _VIQRState * __restrict psenc, size_t * __restrict nresult)
{
	mnemonic_t *m;
	const char *p;
	int ch = 0;

	switch (psenc->chlen) {
	case 0: case 1:
		break;
	default:
		return (EINVAL);
	}
	m = NULL;
	if ((uint32_t)wc <= 0xFF) {
		p = mnemonic_rfc1456[wc & 0xFF];
		if (p != NULL)
			goto mnemonic_found;
		if (n-- < 1)
			goto e2big;
		ch = (unsigned int)wc;
		m = ei->mroot;
		if (psenc->chlen > 0) {
			m = mnemonic_list_find(&m->child, psenc->ch[0]);
			if (m == NULL)
				return (EINVAL);
			psenc->ch[0] = ESCAPE;
		}
		if (mnemonic_list_find(&m->child, ch) == NULL) {
			psenc->chlen = 0;
			m = NULL;
		}
		psenc->ch[psenc->chlen++] = ch;
	} else {
		p = mnemonic_ext_find(wc, &mnemonic_ext[0], mnemonic_ext_size);
		if (p == NULL) {
			*nresult = (size_t)-1;
			return (EILSEQ);
		} else {
mnemonic_found:
			psenc->chlen = 0;
			while (*p != '\0') {
				if (n-- < 1)
					goto e2big;
				psenc->ch[psenc->chlen++] = *p++;
			}
		}
	}
	memcpy(s, psenc->ch, psenc->chlen);
	*nresult = psenc->chlen;
	if (m == ei->mroot) {
		psenc->ch[0] = ch;
		psenc->chlen = 1;
	} else
		psenc->chlen = 0;

	return (0);

e2big:
	*nresult = (size_t)-1;
	return (E2BIG);
}