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
struct mce_evt_llist {int dummy; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MCE_POOLSZ ; 
 int gen_pool_add (struct gen_pool*,unsigned long,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gen_pool_buf ; 
 struct gen_pool* gen_pool_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_destroy (struct gen_pool*) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 struct gen_pool* mce_evt_pool ; 

__attribute__((used)) static int mce_gen_pool_create(void)
{
	struct gen_pool *tmpp;
	int ret = -ENOMEM;

	tmpp = gen_pool_create(ilog2(sizeof(struct mce_evt_llist)), -1);
	if (!tmpp)
		goto out;

	ret = gen_pool_add(tmpp, (unsigned long)gen_pool_buf, MCE_POOLSZ, -1);
	if (ret) {
		gen_pool_destroy(tmpp);
		goto out;
	}

	mce_evt_pool = tmpp;

out:
	return ret;
}