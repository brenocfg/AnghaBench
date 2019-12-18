#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  size_t ssize_t ;
struct TYPE_9__ {scalar_t__ value; struct TYPE_9__* parent; int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ mnemonic_t ;
struct TYPE_10__ {size_t chlen; scalar_t__* ch; } ;
typedef  TYPE_2__ _VIQRState ;
struct TYPE_11__ {scalar_t__ invalid; TYPE_1__* mroot; } ;
typedef  TYPE_3__ _VIQREncodingInfo ;

/* Variables and functions */
 int ESCAPE ; 
 scalar_t__ _ENCODING_IS_STATE_DEPENDENT ; 
 int /*<<< orphan*/  _citrus_VIQR_init_state (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,size_t) ; 
 TYPE_1__* mnemonic_list_find (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_citrus_VIQR_mbrtowc_priv(_VIQREncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s, size_t n,
    _VIQRState * __restrict psenc, size_t * __restrict nresult)
{
	mnemonic_t *m, *m0;
	char *s0;
	wchar_t wc;
	ssize_t i;
	int ch, escape;

	if (*s == NULL) {
		_citrus_VIQR_init_state(ei, psenc);
		*nresult = (size_t)_ENCODING_IS_STATE_DEPENDENT;
		return (0);
	}
	s0 = *s;

	i = 0;
	m = ei->mroot;
	for (escape = 0;;) {
		if (psenc->chlen == i) {
			if (n-- < 1) {
				*s = s0;
				*nresult = (size_t)-2;
				return (0);
			}
			psenc->ch[psenc->chlen++] = *s0++;
		}
		ch = (unsigned char)psenc->ch[i++];
		if (ch == ESCAPE) {
			if (m != ei->mroot)
				break;
			escape = 1;
			continue;
		}
		if (escape != 0)
			break;
		m0 = mnemonic_list_find(&m->child, ch);
		if (m0 == NULL)
			break;
		m = m0;
	}
	while (m != ei->mroot) {
		--i;
		if (m->value != ei->invalid)
			break;
		m = m->parent;
	}
	if (ch == ESCAPE && m != ei->mroot)
		++i;
	psenc->chlen -= i;
	memmove(&psenc->ch[0], &psenc->ch[i], psenc->chlen);
	wc = (m == ei->mroot) ? (wchar_t)ch : m->value;
	if (pwc != NULL)
		*pwc = wc;
	*nresult = (size_t)(wc == 0 ? 0 : s0 - *s);
	*s = s0;

	return (0);
}