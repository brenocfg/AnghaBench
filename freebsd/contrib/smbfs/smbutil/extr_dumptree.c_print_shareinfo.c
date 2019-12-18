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
struct smb_share_info {int mode; int /*<<< orphan*/  usecount; int /*<<< orphan*/  flags; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  sname; } ;

/* Variables and functions */
 char* group_from_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iprintf (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  smb_printb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ss_flags ; 
 char* user_from_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static void
print_shareinfo(struct smb_share_info *sip)
{
	char buf[200];

	iprintf(4, "Share:    %s", sip->sname);
	printf("(%s:%s) %o", user_from_uid(sip->uid, 0), 
	    group_from_gid(sip->gid, 0), sip->mode);
	printf("\n");
	if (!verbose)
		return;
	iprintf(8, "flags:    0x%04x %s\n", sip->flags,
	    smb_printb(buf, sip->flags, ss_flags));
	iprintf(8, "usecount: %d\n", sip->usecount);
}