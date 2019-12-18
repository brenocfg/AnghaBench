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
struct if_clone {int ifc_flags; } ;

/* Variables and functions */

void
ifc_flags_set(struct if_clone *ifc, int flags)
{
	ifc->ifc_flags = flags;
}