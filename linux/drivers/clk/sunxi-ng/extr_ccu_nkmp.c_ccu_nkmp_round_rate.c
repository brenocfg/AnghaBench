#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_10__ {int features; } ;
struct TYPE_9__ {int width; scalar_t__ max; } ;
struct TYPE_8__ {int width; scalar_t__ max; } ;
struct TYPE_7__ {int width; scalar_t__ max; scalar_t__ min; } ;
struct TYPE_6__ {int width; scalar_t__ max; scalar_t__ min; } ;
struct ccu_nkmp {unsigned long fixed_post_div; unsigned long max_rate; TYPE_5__ common; TYPE_4__ p; TYPE_3__ m; TYPE_2__ k; TYPE_1__ n; } ;
struct _ccu_nkmp {int min_n; int max_n; int min_k; int max_k; int min_m; int max_m; int min_p; int max_p; int /*<<< orphan*/  p; int /*<<< orphan*/  m; int /*<<< orphan*/  k; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 unsigned long ccu_nkmp_calc_rate (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccu_nkmp_find_best (unsigned long,unsigned long,struct _ccu_nkmp*) ; 
 struct ccu_nkmp* hw_to_ccu_nkmp (struct clk_hw*) ; 

__attribute__((used)) static long ccu_nkmp_round_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long *parent_rate)
{
	struct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	struct _ccu_nkmp _nkmp;

	if (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nkmp->fixed_post_div;

	if (nkmp->max_rate && rate > nkmp->max_rate) {
		rate = nkmp->max_rate;
		if (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nkmp->fixed_post_div;
		return rate;
	}

	_nkmp.min_n = nkmp->n.min ?: 1;
	_nkmp.max_n = nkmp->n.max ?: 1 << nkmp->n.width;
	_nkmp.min_k = nkmp->k.min ?: 1;
	_nkmp.max_k = nkmp->k.max ?: 1 << nkmp->k.width;
	_nkmp.min_m = 1;
	_nkmp.max_m = nkmp->m.max ?: 1 << nkmp->m.width;
	_nkmp.min_p = 1;
	_nkmp.max_p = nkmp->p.max ?: 1 << ((1 << nkmp->p.width) - 1);

	ccu_nkmp_find_best(*parent_rate, rate, &_nkmp);

	rate = ccu_nkmp_calc_rate(*parent_rate, _nkmp.n, _nkmp.k,
				  _nkmp.m, _nkmp.p);
	if (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate / nkmp->fixed_post_div;

	return rate;
}