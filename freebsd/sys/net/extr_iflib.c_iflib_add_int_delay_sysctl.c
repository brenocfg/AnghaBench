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
typedef  TYPE_1__* if_int_delay_info_t ;
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  ifc_dev; } ;
struct TYPE_6__ {int iidi_offset; int iidi_value; TYPE_2__* iidi_ctx; } ;

/* Variables and functions */
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_sysctl_int_delay ; 

void
iflib_add_int_delay_sysctl(if_ctx_t ctx, const char *name,
	const char *description, if_int_delay_info_t info,
	int offset, int value)
{
	info->iidi_ctx = ctx;
	info->iidi_offset = offset;
	info->iidi_value = value;
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(ctx->ifc_dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(ctx->ifc_dev)),
	    OID_AUTO, name, CTLTYPE_INT|CTLFLAG_RW,
	    info, 0, iflib_sysctl_int_delay, "I", description);
}