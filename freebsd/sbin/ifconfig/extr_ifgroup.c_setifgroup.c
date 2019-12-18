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
struct ifgroupreq {int /*<<< orphan*/  ifgr_group; int /*<<< orphan*/  ifgr_name; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  ifgr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCAIFGROUP ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  memset (struct ifgroupreq*,int /*<<< orphan*/ ,int) ; 
 char const* name ; 
 scalar_t__ strlcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
setifgroup(const char *group_name, int d, int s, const struct afswtch *rafp)
{
	struct ifgroupreq ifgr;

	memset(&ifgr, 0, sizeof(ifgr));
	strlcpy(ifgr.ifgr_name, name, IFNAMSIZ);

	if (group_name[0] && isdigit(group_name[strlen(group_name) - 1]))
		errx(1, "setifgroup: group names may not end in a digit");

	if (strlcpy(ifgr.ifgr_group, group_name, IFNAMSIZ) >= IFNAMSIZ)
		errx(1, "setifgroup: group name too long");
	if (ioctl(s, SIOCAIFGROUP, (caddr_t)&ifgr) == -1 && errno != EEXIST)
		err(1," SIOCAIFGROUP");
}