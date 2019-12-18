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
re_delete(EditLine *el __attribute__((__unused__)),
    wchar_t *d, int dat, int dlen, int num)
{
	wchar_t *a, *b;

	if (num <= 0)
		return;
	if (dat + num >= dlen) {
		d[dat] = '\0';
		return;
	}
	ELRE_DEBUG(1,
	    (__F, "re_delete() starting: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, ct_encode_string(d, &el->el_scratch)));

	/* open up the space for num chars */
	if (num > 0) {
		b = d + dat;
		a = b + num;
		while (a < &d[dlen])
			*b++ = *a++;
		d[dlen] = '\0';	/* just in case */
	}
	ELRE_DEBUG(1,
	    (__F, "re_delete() after delete: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, ct_encode_string(d, &el->el_scratch)));
}