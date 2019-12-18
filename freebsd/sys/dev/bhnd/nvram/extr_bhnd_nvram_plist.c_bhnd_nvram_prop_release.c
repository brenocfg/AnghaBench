#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int refs; struct TYPE_4__* name; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ bhnd_nvram_prop ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  bhnd_nv_free (TYPE_1__*) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_release (int*) ; 

void
bhnd_nvram_prop_release(bhnd_nvram_prop *prop)
{
	BHND_NV_ASSERT(prop->refs >= 1, ("prop over-released"));

	/* Drop reference */
	if (!refcount_release(&prop->refs))
		return;

	/* Free property data */
	bhnd_nvram_val_release(prop->val);
	bhnd_nv_free(prop->name);
	bhnd_nv_free(prop);
}