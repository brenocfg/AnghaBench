#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* nvs_ops; } ;
typedef  TYPE_2__ nvstream_t ;
struct TYPE_12__ {TYPE_5__* nvp_list; } ;
typedef  TYPE_3__ nvpriv_t ;
struct TYPE_13__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_4__ nvlist_t ;
struct TYPE_14__ {int /*<<< orphan*/  nvi_nvp; struct TYPE_14__* nvi_next; } ;
typedef  TYPE_5__ i_nvp_t ;
struct TYPE_10__ {scalar_t__ (* nvs_nvpair ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int (* nvs_nvl_fini ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__*) ; 

__attribute__((used)) static int
nvs_encode_pairs(nvstream_t *nvs, nvlist_t *nvl)
{
	nvpriv_t *priv = (nvpriv_t *)(uintptr_t)nvl->nvl_priv;
	i_nvp_t *curr;

	/*
	 * Walk nvpair in list and encode each nvpair
	 */
	for (curr = priv->nvp_list; curr != NULL; curr = curr->nvi_next)
		if (nvs->nvs_ops->nvs_nvpair(nvs, &curr->nvi_nvp, NULL) != 0)
			return (EFAULT);

	return (nvs->nvs_ops->nvs_nvl_fini(nvs));
}