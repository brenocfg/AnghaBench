#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long i1; long i2; int min_lo; int min_hi; } ;
typedef  TYPE_1__ xdpsplit_t ;
typedef  int /*<<< orphan*/  xdalgoenv_t ;
struct TYPE_7__ {unsigned long* ha; char* rchg; long* rindex; } ;
typedef  TYPE_2__ diffdata_t ;

/* Variables and functions */
 scalar_t__ xdl_split (unsigned long const*,long,long,unsigned long const*,long,long,long*,long*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 

int xdl_recs_cmp(diffdata_t *dd1, long off1, long lim1,
		 diffdata_t *dd2, long off2, long lim2,
		 long *kvdf, long *kvdb, int need_min, xdalgoenv_t *xenv) {
	unsigned long const *ha1 = dd1->ha, *ha2 = dd2->ha;

	/*
	 * Shrink the box by walking through each diagonal snake (SW and NE).
	 */
	for (; off1 < lim1 && off2 < lim2 && ha1[off1] == ha2[off2]; off1++, off2++);
	for (; off1 < lim1 && off2 < lim2 && ha1[lim1 - 1] == ha2[lim2 - 1]; lim1--, lim2--);

	/*
	 * If one dimension is empty, then all records on the other one must
	 * be obviously changed.
	 */
	if (off1 == lim1) {
		char *rchg2 = dd2->rchg;
		long *rindex2 = dd2->rindex;

		for (; off2 < lim2; off2++)
			rchg2[rindex2[off2]] = 1;
	} else if (off2 == lim2) {
		char *rchg1 = dd1->rchg;
		long *rindex1 = dd1->rindex;

		for (; off1 < lim1; off1++)
			rchg1[rindex1[off1]] = 1;
	} else {
		xdpsplit_t spl;
		spl.i1 = spl.i2 = 0;

		/*
		 * Divide ...
		 */
		if (xdl_split(ha1, off1, lim1, ha2, off2, lim2, kvdf, kvdb,
			      need_min, &spl, xenv) < 0) {

			return -1;
		}

		/*
		 * ... et Impera.
		 */
		if (xdl_recs_cmp(dd1, off1, spl.i1, dd2, off2, spl.i2,
				 kvdf, kvdb, spl.min_lo, xenv) < 0 ||
		    xdl_recs_cmp(dd1, spl.i1, lim1, dd2, spl.i2, lim2,
				 kvdf, kvdb, spl.min_hi, xenv) < 0) {

			return -1;
		}
	}

	return 0;
}