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
typedef  TYPE_1__* devclass_t ;
struct TYPE_4__ {int /*<<< orphan*/ * sysctl_tree; int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  DEVCLASS_SYSCTL_PARENT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dev ; 
 int /*<<< orphan*/  devclass_sysctl_handler ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devclass_sysctl_init(devclass_t dc)
{

	if (dc->sysctl_tree != NULL)
		return;
	sysctl_ctx_init(&dc->sysctl_ctx);
	dc->sysctl_tree = SYSCTL_ADD_NODE(&dc->sysctl_ctx,
	    SYSCTL_STATIC_CHILDREN(_dev), OID_AUTO, dc->name,
	    CTLFLAG_RD, NULL, "");
	SYSCTL_ADD_PROC(&dc->sysctl_ctx, SYSCTL_CHILDREN(dc->sysctl_tree),
	    OID_AUTO, "%parent", CTLTYPE_STRING | CTLFLAG_RD,
	    dc, DEVCLASS_SYSCTL_PARENT, devclass_sysctl_handler, "A",
	    "parent class");
}