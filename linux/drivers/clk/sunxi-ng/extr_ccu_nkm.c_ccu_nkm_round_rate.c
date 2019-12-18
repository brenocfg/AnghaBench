#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_8__ {int features; } ;
struct TYPE_7__ {int width; scalar_t__ max; } ;
struct TYPE_6__ {int width; scalar_t__ max; scalar_t__ min; } ;
struct TYPE_5__ {int width; scalar_t__ max; scalar_t__ min; } ;
struct ccu_nkm {unsigned long fixed_post_div; TYPE_4__ common; TYPE_3__ m; TYPE_2__ k; TYPE_1__ n; } ;
struct ccu_mux_internal {int dummy; } ;
struct _ccu_nkm {int min_n; int max_n; int min_k; int max_k; int min_m; int max_m; unsigned long n; unsigned long k; unsigned long m; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 int /*<<< orphan*/  ccu_nkm_find_best (unsigned long,unsigned long,struct _ccu_nkm*) ; 

__attribute__((used)) static unsigned long ccu_nkm_round_rate(struct ccu_mux_internal *mux,
					struct clk_hw *hw,
					unsigned long *parent_rate,
					unsigned long rate,
					void *data)
{
	struct ccu_nkm *nkm = data;
	struct _ccu_nkm _nkm;

	_nkm.min_n = nkm->n.min ?: 1;
	_nkm.max_n = nkm->n.max ?: 1 << nkm->n.width;
	_nkm.min_k = nkm->k.min ?: 1;
	_nkm.max_k = nkm->k.max ?: 1 << nkm->k.width;
	_nkm.min_m = 1;
	_nkm.max_m = nkm->m.max ?: 1 << nkm->m.width;

	if (nkm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= nkm->fixed_post_div;

	ccu_nkm_find_best(*parent_rate, rate, &_nkm);

	rate = *parent_rate * _nkm.n * _nkm.k / _nkm.m;

	if (nkm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nkm->fixed_post_div;

	return rate;
}