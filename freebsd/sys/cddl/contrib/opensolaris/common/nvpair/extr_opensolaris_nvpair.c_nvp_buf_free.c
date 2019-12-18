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
typedef  int /*<<< orphan*/  nvpriv_t ;
struct TYPE_6__ {size_t nvp_size; } ;
typedef  TYPE_1__ nvpair_t ;
struct TYPE_7__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_2__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR2I_NVP (TYPE_1__*) ; 
 int /*<<< orphan*/  i_nvp_t ; 
 int /*<<< orphan*/  nv_mem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nvi_nvp ; 
 size_t offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvp_buf_free(nvlist_t *nvl, nvpair_t *nvp)
{
	nvpriv_t *priv = (nvpriv_t *)(uintptr_t)nvl->nvl_priv;
	size_t nvsize = nvp->nvp_size + offsetof(i_nvp_t, nvi_nvp);

	nv_mem_free(priv, NVPAIR2I_NVP(nvp), nvsize);
}