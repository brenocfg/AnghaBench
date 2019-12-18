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
struct node_host {TYPE_1__* tail; } ;
struct ifgroupreq {int ifgr_len; struct ifg_req* ifgr_groups; int /*<<< orphan*/  ifgr_name; } ;
struct ifg_req {int /*<<< orphan*/  ifgrq_member; } ;
typedef  int /*<<< orphan*/  ifgr ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {struct node_host* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFGMEMB ; 
 int /*<<< orphan*/  bzero (struct ifgroupreq*,int) ; 
 struct ifg_req* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct ifg_req*) ; 
 int get_query_socket () ; 
 struct node_host* ifa_lookup (int /*<<< orphan*/ ,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_a_group (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

struct node_host *
ifa_grouplookup(char *ifa_name, int flags)
{
	struct ifg_req		*ifg;
	struct ifgroupreq	 ifgr;
	int			 s, len;
	struct node_host	*n, *h = NULL;

	s = get_query_socket();
	len = is_a_group(ifa_name);
	if (len == 0)
		return (NULL);
	bzero(&ifgr, sizeof(ifgr));
	strlcpy(ifgr.ifgr_name, ifa_name, sizeof(ifgr.ifgr_name));
	ifgr.ifgr_len = len;
	if ((ifgr.ifgr_groups = calloc(1, len)) == NULL)
		err(1, "calloc");
	if (ioctl(s, SIOCGIFGMEMB, (caddr_t)&ifgr) == -1)
		err(1, "SIOCGIFGMEMB");

	for (ifg = ifgr.ifgr_groups; ifg && len >= sizeof(struct ifg_req);
	    ifg++) {
		len -= sizeof(struct ifg_req);
		if ((n = ifa_lookup(ifg->ifgrq_member, flags)) == NULL)
			continue;
		if (h == NULL)
			h = n;
		else {
			h->tail->next = n;
			h->tail = n->tail;
		}
	}
	free(ifgr.ifgr_groups);

	return (h);
}