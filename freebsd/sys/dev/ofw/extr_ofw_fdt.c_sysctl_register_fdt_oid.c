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

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_OPAQUE ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw_fdt ; 
 int /*<<< orphan*/ * fdtp ; 
 int /*<<< orphan*/  sysctl_handle_dtb ; 

__attribute__((used)) static void
sysctl_register_fdt_oid(void *arg)
{

	/* If there is no FDT registered, skip adding the sysctl */
	if (fdtp == NULL)
		return;

	SYSCTL_ADD_PROC(NULL, SYSCTL_STATIC_CHILDREN(_hw_fdt), OID_AUTO, "dtb",
	    CTLTYPE_OPAQUE | CTLFLAG_RD, NULL, 0, sysctl_handle_dtb, "",
	    "Device Tree Blob");
}