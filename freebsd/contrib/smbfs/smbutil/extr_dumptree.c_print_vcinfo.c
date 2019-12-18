#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t sv_proto; int /*<<< orphan*/  sv_maxvcs; int /*<<< orphan*/  sv_maxmux; int /*<<< orphan*/  sv_caps; int /*<<< orphan*/  sv_sm; } ;
struct smb_vc_info {char* srvname; char* vcname; int mode; size_t iodstate; TYPE_1__ sopt; int /*<<< orphan*/  usecount; int /*<<< orphan*/  flags; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_caps ; 
 int /*<<< orphan*/ * conn_proto ; 
 char* group_from_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iod_state ; 
 int /*<<< orphan*/  iprintf (int,char*,size_t,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  smb_printb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* user_from_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_flags ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static void
print_vcinfo(struct smb_vc_info *vip)
{
	char buf[200];

	printf("VC: \\\\%s\\%s\n", vip->srvname, vip->vcname);
	printf("(%s:%s) %o", user_from_uid(vip->uid, 0), 
	    group_from_gid(vip->gid, 0), vip->mode);
	printf("\n");
	if (!verbose)
		return;
	iprintf(4, "state:    %s\n", iod_state[vip->iodstate]);
	iprintf(4, "flags:    0x%04x %s\n", vip->flags,
	    smb_printb(buf, vip->flags, vc_flags));
	iprintf(4, "usecount: %d\n", vip->usecount);
	iprintf(4, "dialect:  %d (%s)\n", vip->sopt.sv_proto, conn_proto[vip->sopt.sv_proto]);
	iprintf(4, "smode:    %d\n", vip->sopt.sv_sm);
	iprintf(4, "caps:     0x%04x %s\n", vip->sopt.sv_caps,
	    smb_printb(buf, vip->sopt.sv_caps, conn_caps));
	iprintf(4, "maxmux:   %d\n", vip->sopt.sv_maxmux);
	iprintf(4, "maxvcs:   %d\n", vip->sopt.sv_maxvcs);
}