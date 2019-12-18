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
typedef  scalar_t__ u_int ;
struct fatcache {scalar_t__ fc_frcn; } ;
struct denode {struct fatcache* de_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DETOV (struct denode*) ; 
 scalar_t__ FCE_EMPTY ; 
 int FC_SIZE ; 

void
fc_purge(struct denode *dep, u_int frcn)
{
	int i;
	struct fatcache *fcp;

	ASSERT_VOP_ELOCKED(DETOV(dep), "fc_purge");

	fcp = dep->de_fc;
	for (i = 0; i < FC_SIZE; i++, fcp++) {
		if (fcp->fc_frcn >= frcn)
			fcp->fc_frcn = FCE_EMPTY;
	}
}