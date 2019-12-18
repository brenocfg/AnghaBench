#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct TYPE_5__ {scalar_t__ page; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ BUFHEAD ;

/* Variables and functions */
 scalar_t__ FREESPACE (int*) ; 
 int FULL_KEY_DATA ; 
 int OVFLPAGE ; 
 TYPE_1__* __get_buf (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

u_int16_t
__find_last_page(HTAB *hashp, BUFHEAD **bpp)
{
	BUFHEAD *bufp;
	u_int16_t *bp, pageno;
	int n;

	bufp = *bpp;
	bp = (u_int16_t *)bufp->page;
	for (;;) {
		n = bp[0];

		/*
		 * This is the last page if: the tag is FULL_KEY_DATA and
		 * either only 2 entries OVFLPAGE marker is explicit there
		 * is freespace on the page.
		 */
		if (bp[2] == FULL_KEY_DATA &&
		    ((n == 2) || (bp[n] == OVFLPAGE) || (FREESPACE(bp))))
			break;

		pageno = bp[n - 1];
		bufp = __get_buf(hashp, pageno, bufp, 0);
		if (!bufp)
			return (0);	/* Need to indicate an error! */
		bp = (u_int16_t *)bufp->page;
	}

	*bpp = bufp;
	if (bp[0] > 2)
		return (bp[3]);
	else
		return (0);
}