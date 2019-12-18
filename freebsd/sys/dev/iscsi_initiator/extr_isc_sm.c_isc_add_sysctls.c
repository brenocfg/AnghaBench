#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  targetAddress; int /*<<< orphan*/  targetName; } ;
struct TYPE_7__ {int /*<<< orphan*/  douio; int /*<<< orphan*/  oid; int /*<<< orphan*/  clist; TYPE_2__ opt; int /*<<< orphan*/  dev; TYPE_1__* isc; int /*<<< orphan*/  sid; } ;
typedef  TYPE_3__ isc_session_t ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ devtoname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_dump_stats ; 
 int /*<<< orphan*/  sdebug (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_handle_string ; 

__attribute__((used)) static void
isc_add_sysctls(isc_session_t *sp)
{
     debug_called(8);
     sdebug(6, "sid=%d %s", sp->sid, devtoname(sp->dev));

     sysctl_ctx_init(&sp->clist);
     sp->oid = SYSCTL_ADD_NODE(&sp->clist,
			       SYSCTL_CHILDREN(sp->isc->oid),
			       OID_AUTO,
			       devtoname(sp->dev) + 5, // iscsi0
			       CTLFLAG_RD,
			       0,
			       "initiator");
     SYSCTL_ADD_PROC(&sp->clist,
		     SYSCTL_CHILDREN(sp->oid),
		     OID_AUTO,
		     "targetname",
		     CTLTYPE_STRING | CTLFLAG_RD,
		     (void *)&sp->opt.targetName, 0,
		     sysctl_handle_string, "A", "target name");

     SYSCTL_ADD_PROC(&sp->clist,
		     SYSCTL_CHILDREN(sp->oid),
		     OID_AUTO,
		     "targeaddress",
		     CTLTYPE_STRING | CTLFLAG_RD,
		     (void *)&sp->opt.targetAddress, 0,
		     sysctl_handle_string, "A", "target address");

     SYSCTL_ADD_PROC(&sp->clist,
		     SYSCTL_CHILDREN(sp->oid),
		     OID_AUTO,
		     "stats",
		     CTLTYPE_STRING | CTLFLAG_RD,
		     (void *)sp, 0,
		     isc_dump_stats, "A", "statistics");

     SYSCTL_ADD_INT(&sp->clist,
		     SYSCTL_CHILDREN(sp->oid),
		     OID_AUTO,
		     "douio",
		     CTLFLAG_RW,
		     &sp->douio, 0, "enable uio on read");
}