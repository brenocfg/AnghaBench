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
struct ifgroupreq {int ifgr_len; struct ifg_req* ifgr_groups; int /*<<< orphan*/  ifgr_name; } ;
struct ifg_req {char* ifgrq_member; } ;
typedef  int /*<<< orphan*/  ifgr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTTY ; 
 int /*<<< orphan*/  SIOCGIFGMEMB ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bzero (struct ifgroupreq*,int) ; 
 struct ifg_req* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_code ; 
 int /*<<< orphan*/  free (struct ifg_req*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
printgroup(const char *groupname)
{
	struct ifgroupreq	 ifgr;
	struct ifg_req		*ifg;
	int			 len, cnt = 0;
	int			 s;

	s = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (s == -1)
		err(1, "socket(AF_LOCAL,SOCK_DGRAM)");
	bzero(&ifgr, sizeof(ifgr));
	strlcpy(ifgr.ifgr_name, groupname, sizeof(ifgr.ifgr_name));
	if (ioctl(s, SIOCGIFGMEMB, (caddr_t)&ifgr) == -1) {
		if (errno == EINVAL || errno == ENOTTY ||
		    errno == ENOENT)
			exit(exit_code);
		else
			err(1, "SIOCGIFGMEMB");
	}

	len = ifgr.ifgr_len;
	if ((ifgr.ifgr_groups = calloc(1, len)) == NULL)
		err(1, "printgroup");
	if (ioctl(s, SIOCGIFGMEMB, (caddr_t)&ifgr) == -1)
		err(1, "SIOCGIFGMEMB");

	for (ifg = ifgr.ifgr_groups; ifg && len >= sizeof(struct ifg_req);
	    ifg++) {
		len -= sizeof(struct ifg_req);
		printf("%s\n", ifg->ifgrq_member);
		cnt++;
	}
	free(ifgr.ifgr_groups);

	exit(exit_code);
}