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
struct ifgroupreq {int /*<<< orphan*/  ifgr_name; } ;
typedef  int /*<<< orphan*/  ifgr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCGIFGMEMB ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int get_query_socket () ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifgroupreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
interface_group(const char *ifname)
{
	int			s;
	struct ifgroupreq	ifgr;

	if (ifname == NULL || !ifname[0])
		return (0);

	s = get_query_socket();

	memset(&ifgr, 0, sizeof(ifgr));
	strlcpy(ifgr.ifgr_name, ifname, IFNAMSIZ);
	if (ioctl(s, SIOCGIFGMEMB, (caddr_t)&ifgr) == -1) {
		if (errno == ENOENT)
			return (0);
		else
			err(1, "SIOCGIFGMEMB");
	}

	return (1);
}