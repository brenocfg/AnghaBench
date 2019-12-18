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
typedef  int /*<<< orphan*/  __Char ;
typedef  int Char ;

/* Variables and functions */
 char const EOS ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
#define  M_ALL 130 
 int const M_END ; 
 int M_MASK ; 
#define  M_ONE 129 
 int const M_RNG ; 
#define  M_SET 128 
 size_t One_Char_mbtowc (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  globcharcoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t one_mbtowc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  samecase (int /*<<< orphan*/ ) ; 

__attribute__((used)) static  int
match(const char *name, const Char *pat, const Char *patend, int m_not)
{
    int ok, negate_range;
    const Char *patNext;
    const char *nameNext, *nameStart, *nameEnd;
    Char c;

    patNext = pat;
    nameStart = nameNext = name;
    nameEnd = NULL;

    while (pat < patend || *name) {
	size_t lwk, pwk;
	__Char wc, wk, wc1;

	c = *pat; /* Only for M_MASK bits */
	if (*name == EOS)
		nameEnd = name;

	pwk = One_Char_mbtowc(&wc, pat, MB_LEN_MAX);
	lwk = one_mbtowc(&wk, name, MB_LEN_MAX);
	switch (c & M_MASK) {
	case M_ALL:
	    while ((*(pat + pwk) & M_MASK) == M_ALL) {
		pat += pwk;
		pwk = One_Char_mbtowc(&wc, pat, MB_LEN_MAX);
	    }
	    patNext = pat;
	    nameNext = name + lwk;
	    pat += pwk;
	    continue;
	case M_ONE:
	    if (*name == EOS)
		break;
	    name += lwk;
	    pat += pwk;
	    continue;
	case M_SET:
	    ok = 0;
	    if (*name == EOS)
		break;
	    pat += pwk;
	    pwk = One_Char_mbtowc(&wc, pat, MB_LEN_MAX);
	    name += lwk;
	    if ((negate_range = ((*pat & M_MASK) == m_not)) != 0) {
		pat += pwk;
		pwk = One_Char_mbtowc(&wc, pat, MB_LEN_MAX);
	    }
	    wc1 = wc;
	    while ((*pat & M_MASK) != M_END) {
		if ((*pat & M_MASK) == M_RNG) {
		    __Char wc2;

		    pat += pwk;
		    pwk = One_Char_mbtowc(&wc2, pat, MB_LEN_MAX);
		    if (globcharcoll(wc1, wk, 0) <= 0 &&
			globcharcoll(wk, wc2, 0) <= 0)
			ok = 1;
		} else if (wc == wk)
		    ok = 1;
		pat += pwk;
		wc1 = wc;
		pwk = One_Char_mbtowc(&wc, pat, MB_LEN_MAX);
	    }
	    pat += pwk;
	    pwk = One_Char_mbtowc(&wc, pat, MB_LEN_MAX);
	    if (ok == negate_range)
		break;
	    continue;
	default:
	    if (*name == EOS || samecase(wk) != samecase(wc))
		break;
	    name += lwk;
	    pat += pwk;
	    continue;
	}
	if (nameNext != nameStart
	    && (nameEnd == NULL || nameNext <= nameEnd)) {
	    pat = patNext;
	    name = nameNext;
	    continue;
	}
	return 0;
    }
    return 1;
}