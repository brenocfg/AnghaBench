#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ha; } ;
typedef  TYPE_1__ xrecord_t ;
struct TYPE_6__ {long nrec; long dstart; long dend; TYPE_1__** recs; } ;
typedef  TYPE_2__ xdfile_t ;

/* Variables and functions */
 long XDL_MIN (long,long) ; 

__attribute__((used)) static int xdl_trim_ends(xdfile_t *xdf1, xdfile_t *xdf2) {
	long i, lim;
	xrecord_t **recs1, **recs2;

	recs1 = xdf1->recs;
	recs2 = xdf2->recs;
	for (i = 0, lim = XDL_MIN(xdf1->nrec, xdf2->nrec); i < lim;
	     i++, recs1++, recs2++)
		if ((*recs1)->ha != (*recs2)->ha)
			break;

	xdf1->dstart = xdf2->dstart = i;

	recs1 = xdf1->recs + xdf1->nrec - 1;
	recs2 = xdf2->recs + xdf2->nrec - 1;
	for (lim -= i, i = 0; i < lim; i++, recs1--, recs2--)
		if ((*recs1)->ha != (*recs2)->ha)
			break;

	xdf1->dend = xdf1->nrec - i - 1;
	xdf2->dend = xdf2->nrec - i - 1;

	return 0;
}