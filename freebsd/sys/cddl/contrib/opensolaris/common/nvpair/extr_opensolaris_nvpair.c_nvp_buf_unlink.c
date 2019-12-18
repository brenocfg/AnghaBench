#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* nvp_last; TYPE_3__* nvp_list; TYPE_3__* nvp_curr; } ;
typedef  TYPE_1__ nvpriv_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_7__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_2__ nvlist_t ;
struct TYPE_8__ {struct TYPE_8__* nvi_prev; struct TYPE_8__* nvi_next; } ;
typedef  TYPE_3__ i_nvp_t ;

/* Variables and functions */
 TYPE_3__* NVPAIR2I_NVP (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvp_buf_unlink(nvlist_t *nvl, nvpair_t *nvp)
{
	nvpriv_t *priv = (nvpriv_t *)(uintptr_t)nvl->nvl_priv;
	i_nvp_t *curr = NVPAIR2I_NVP(nvp);

	/*
	 * protect nvlist_next_nvpair() against walking on freed memory.
	 */
	if (priv->nvp_curr == curr)
		priv->nvp_curr = curr->nvi_next;

	if (curr == priv->nvp_list)
		priv->nvp_list = curr->nvi_next;
	else
		curr->nvi_prev->nvi_next = curr->nvi_next;

	if (curr == priv->nvp_last)
		priv->nvp_last = curr->nvi_prev;
	else
		curr->nvi_next->nvi_prev = curr->nvi_prev;
}