#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct TYPE_11__ {int addr; struct TYPE_11__* ovfl; int /*<<< orphan*/  flags; scalar_t__ page; } ;
struct TYPE_10__ {int FFACTOR; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ BUFHEAD ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MOD ; 
 int DEF_FFACTOR ; 
 int FREESPACE (int*) ; 
 int MIN_FFACTOR ; 
 int OFFSET (int*) ; 
 int OVFLPAGE ; 
 int OVFLSIZE ; 
 TYPE_2__* __get_buf (TYPE_1__*,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  hash_overflows ; 
 int overflow_page (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

BUFHEAD *
__add_ovflpage(HTAB *hashp, BUFHEAD *bufp)
{
	u_int16_t *sp, ndx, ovfl_num;
#ifdef DEBUG1
	int tmp1, tmp2;
#endif
	sp = (u_int16_t *)bufp->page;

	/* Check if we are dynamically determining the fill factor */
	if (hashp->FFACTOR == DEF_FFACTOR) {
		hashp->FFACTOR = sp[0] >> 1;
		if (hashp->FFACTOR < MIN_FFACTOR)
			hashp->FFACTOR = MIN_FFACTOR;
	}
	bufp->flags |= BUF_MOD;
	ovfl_num = overflow_page(hashp);
#ifdef DEBUG1
	tmp1 = bufp->addr;
	tmp2 = bufp->ovfl ? bufp->ovfl->addr : 0;
#endif
	if (!ovfl_num || !(bufp->ovfl = __get_buf(hashp, ovfl_num, bufp, 1)))
		return (NULL);
	bufp->ovfl->flags |= BUF_MOD;
#ifdef DEBUG1
	(void)fprintf(stderr, "ADDOVFLPAGE: %d->ovfl was %d is now %d\n",
	    tmp1, tmp2, bufp->ovfl->addr);
#endif
	ndx = sp[0];
	/*
	 * Since a pair is allocated on a page only if there's room to add
	 * an overflow page, we know that the OVFL information will fit on
	 * the page.
	 */
	sp[ndx + 4] = OFFSET(sp);
	sp[ndx + 3] = FREESPACE(sp) - OVFLSIZE;
	sp[ndx + 1] = ovfl_num;
	sp[ndx + 2] = OVFLPAGE;
	sp[0] = ndx + 2;
#ifdef HASH_STATISTICS
	hash_overflows++;
#endif
	return (bufp->ovfl);
}