#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  el_scratch; } ;
typedef  TYPE_1__ EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  ELRE_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __F ; 
 int /*<<< orphan*/  ct_encode_string (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
/*ARGSUSED*/
re_insert(EditLine *el __attribute__((__unused__)),
    wchar_t *d, int dat, int dlen, wchar_t *s, int num)
{
	wchar_t *a, *b;

	if (num <= 0)
		return;
	if (num > dlen - dat)
		num = dlen - dat;

	ELRE_DEBUG(1,
	    (__F, "re_insert() starting: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, ct_encode_string(d, &el->el_scratch)));
	ELRE_DEBUG(1, (__F, "s == \"%s\"\n", ct_encode_string(s,
	    &el->el_scratch)));

	/* open up the space for num chars */
	if (num > 0) {
		b = d + dlen - 1;
		a = b - num;
		while (a >= &d[dat])
			*b-- = *a--;
		d[dlen] = '\0';	/* just in case */
	}

	ELRE_DEBUG(1, (__F,
		"re_insert() after insert: %d at %d max %d, d == \"%s\"\n",
		num, dat, dlen, ct_encode_string(d, &el->el_scratch)));
	ELRE_DEBUG(1, (__F, "s == \"%s\"\n", ct_encode_string(s,
		&el->el_scratch)));

	/* copy the characters */
	for (a = d + dat; (a < d + dlen) && (num > 0); num--)
		*a++ = *s++;

#ifdef notyet
        /* ct_encode_string() uses a static buffer, so we can't conveniently
         * encode both d & s here */
	ELRE_DEBUG(1,
	    (__F, "re_insert() after copy: %d at %d max %d, %s == \"%s\"\n",
	    num, dat, dlen, d, s));
	ELRE_DEBUG(1, (__F, "s == \"%s\"\n", s));
#endif
}