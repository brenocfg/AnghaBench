#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_6__ {int features; } ;
struct TYPE_5__ {int width; scalar_t__ max; scalar_t__ min; } ;
struct TYPE_4__ {int width; scalar_t__ max; scalar_t__ min; } ;
struct ccu_nk {unsigned long fixed_post_div; TYPE_3__ common; TYPE_2__ k; TYPE_1__ n; } ;
struct _ccu_nk {int min_n; int max_n; int min_k; int max_k; unsigned long n; unsigned long k; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 int /*<<< orphan*/  ccu_nk_find_best (unsigned long,unsigned long,struct _ccu_nk*) ; 
 struct ccu_nk* hw_to_ccu_nk (struct clk_hw*) ; 

__attribute__((used)) static long ccu_nk_round_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long *parent_rate)
{
	struct ccu_nk *nk = hw_to_ccu_nk(hw);
	struct _ccu_nk _nk;

	if (nk->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nk->fixed_post_div;

	_nk.min_n = nk->n.min ?: 1;
	_nk.max_n = nk->n.max ?: 1 << nk->n.width;
	_nk.min_k = nk->k.min ?: 1;
	_nk.max_k = nk->k.max ?: 1 << nk->k.width;

	ccu_nk_find_best(*parent_rate, rate, &_nk);
	rate = *parent_rate * _nk.n * _nk.k;

	if (nk->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate = rate / nk->fixed_post_div;

	return rate;
}