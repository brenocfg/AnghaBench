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
struct smb_share_info {int /*<<< orphan*/  sname; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  type; int /*<<< orphan*/  tid; int /*<<< orphan*/  usecount; int /*<<< orphan*/  itype; } ;
struct TYPE_2__ {int /*<<< orphan*/  co_flags; int /*<<< orphan*/  co_usecount; } ;
struct smb_share {char* ss_name; TYPE_1__ obj; int /*<<< orphan*/  ss_mode; int /*<<< orphan*/  ss_grp; int /*<<< orphan*/  ss_uid; int /*<<< orphan*/  ss_type; int /*<<< orphan*/  ss_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB_INFO_SHARE ; 
 int /*<<< orphan*/  bzero (struct smb_share_info*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int
smb_share_getinfo(struct smb_share *ssp, struct smb_share_info *sip)
{
	bzero(sip, sizeof(struct smb_share_info));
	sip->itype = SMB_INFO_SHARE;
	sip->usecount = ssp->obj.co_usecount;
	sip->tid  = ssp->ss_tid;
	sip->type= ssp->ss_type;
	sip->uid = ssp->ss_uid;
	sip->gid = ssp->ss_grp;
	sip->mode= ssp->ss_mode;
	sip->flags = ssp->obj.co_flags;
	snprintf(sip->sname, sizeof(sip->sname), "%s", ssp->ss_name);
	return 0;
}