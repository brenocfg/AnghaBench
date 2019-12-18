#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpriv_t ;
struct TYPE_9__ {scalar_t__ nvl_priv; int /*<<< orphan*/  nvl_nvflag; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * nv_priv_alloc_embedded (int /*<<< orphan*/ *) ; 
 int nvlist_copy_pairs (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_free (TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvlist_copy_embedded(nvlist_t *nvl, nvlist_t *onvl, nvlist_t *emb_nvl)
{
	nvpriv_t *priv;
	int err;

	if ((priv = nv_priv_alloc_embedded((nvpriv_t *)(uintptr_t)
	    nvl->nvl_priv)) == NULL)
		return (ENOMEM);

	nvlist_init(emb_nvl, onvl->nvl_nvflag, priv);

	if ((err = nvlist_copy_pairs(onvl, emb_nvl)) != 0) {
		nvlist_free(emb_nvl);
		emb_nvl->nvl_priv = 0;
	}

	return (err);
}