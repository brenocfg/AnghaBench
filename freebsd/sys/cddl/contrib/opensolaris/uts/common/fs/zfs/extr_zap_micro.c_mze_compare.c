#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mze_cd; int /*<<< orphan*/  mze_hash; } ;
typedef  TYPE_1__ mzap_ent_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
mze_compare(const void *arg1, const void *arg2)
{
	const mzap_ent_t *mze1 = arg1;
	const mzap_ent_t *mze2 = arg2;

	int cmp = AVL_CMP(mze1->mze_hash, mze2->mze_hash);
	if (likely(cmp))
		return (cmp);

	return (AVL_CMP(mze1->mze_cd, mze2->mze_cd));
}