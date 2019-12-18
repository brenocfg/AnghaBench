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
typedef  int wchar_t ;
struct TYPE_4__ {char* str; int lastch; int cnt; int* set; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ STR ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int NCHARS_SB ; 
 int OOBCH ; 
 int /*<<< orphan*/  RANGE ; 
 int /*<<< orphan*/  SET ; 
 int backslash (TYPE_1__*,int*) ; 
 scalar_t__ charcoll (void const*,void const*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* malloc (int) ; 
 size_t mbrtowc (int*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mergesort (int*,int,int,scalar_t__ (*) (void const*,void const*)) ; 

__attribute__((used)) static int
genrange(STR *s, int was_octal)
{
	int stopval, octal;
	char *savestart;
	int n, cnt, *p;
	size_t clen;
	wchar_t wc;

	octal = 0;
	savestart = s->str;
	if (*++s->str == '\\')
		stopval = backslash(s, &octal);
	else {
		clen = mbrtowc(&wc, s->str, MB_LEN_MAX, NULL);
		if (clen == (size_t)-1 || clen == (size_t)-2)
			errc(1, EILSEQ, NULL);
		stopval = wc;
		s->str += clen;
	}
	/*
	 * XXX Characters are not ordered according to collating sequence in
	 * multibyte locales.
	 */
	if (octal || was_octal || MB_CUR_MAX > 1) {
		if (stopval < s->lastch) {
			s->str = savestart;
			return (0);
		}
		s->cnt = stopval - s->lastch + 1;
		s->state = RANGE;
		--s->lastch;
		return (1);
	}
	if (charcoll((const void *)&stopval, (const void *)&(s->lastch)) < 0) {
		s->str = savestart;
		return (0);
	}
	if ((s->set = p = malloc((NCHARS_SB + 1) * sizeof(int))) == NULL)
		err(1, "genrange() malloc");
	for (cnt = 0; cnt < NCHARS_SB; cnt++)
		if (charcoll((const void *)&cnt, (const void *)&(s->lastch)) >= 0 &&
		    charcoll((const void *)&cnt, (const void *)&stopval) <= 0)
			*p++ = cnt;
	*p = OOBCH;
	n = p - s->set;

	s->cnt = 0;
	s->state = SET;
	if (n > 1)
		mergesort(s->set, n, sizeof(*(s->set)), charcoll);
	return (1);
}