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
struct malloc_type_internal {scalar_t__ mti_zone; } ;
struct malloc_type {struct malloc_type_internal* ks_handle; } ;

/* Variables and functions */

__attribute__((used)) static void
mtp_set_subzone(struct malloc_type *mtp)
{
	struct malloc_type_internal *mtip;

	mtip = mtp->ks_handle;
	mtip->mti_zone = 0;
}