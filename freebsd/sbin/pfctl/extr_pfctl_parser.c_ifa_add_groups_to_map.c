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
struct ifgroupreq {int ifgr_len; struct ifg_req* ifgr_groups; int /*<<< orphan*/  ifgr_name; } ;
struct ifg_req {char* ifgrq_group; } ;
typedef  int /*<<< orphan*/  ifgr2 ;
typedef  int /*<<< orphan*/  ifgr ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {char* key; int* data; } ;
typedef  TYPE_1__ ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  FIND ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCGIFGMEMB ; 
 int /*<<< orphan*/  SIOCGIFGROUP ; 
 int /*<<< orphan*/  bzero (struct ifgroupreq*,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct ifg_req*) ; 
 int get_query_socket () ; 
 scalar_t__ hsearch_r (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isgroup_map ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memset (struct ifgroupreq*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
ifa_add_groups_to_map(char *ifa_name)
{
	int			 s, len;
	struct ifgroupreq	 ifgr;
	struct ifg_req		*ifg;

	s = get_query_socket();

	/* Get size of group list for this interface */
	memset(&ifgr, 0, sizeof(ifgr));
	strlcpy(ifgr.ifgr_name, ifa_name, IFNAMSIZ);
	if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1)
		err(1, "SIOCGIFGROUP");

	/* Retrieve group list for this interface */
	len = ifgr.ifgr_len;
	ifgr.ifgr_groups =
	    (struct ifg_req *)calloc(len / sizeof(struct ifg_req),
		sizeof(struct ifg_req));
	if (ifgr.ifgr_groups == NULL)
		err(1, "calloc");
	if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1)
		err(1, "SIOCGIFGROUP");

	ifg = ifgr.ifgr_groups;
	for (; ifg && len >= sizeof(struct ifg_req); ifg++) {
		len -= sizeof(struct ifg_req);
		if (strcmp(ifg->ifgrq_group, "all")) {
			ENTRY	 		 item;
			ENTRY			*ret_item;
			int			*answer;
	
			item.key = ifg->ifgrq_group;
			if (hsearch_r(item, FIND, &ret_item, &isgroup_map) == 0) {
				struct ifgroupreq	 ifgr2;

				/* Don't know the answer yet */
				if ((answer = malloc(sizeof(int))) == NULL)
					err(1, "malloc");

				bzero(&ifgr2, sizeof(ifgr2));
				strlcpy(ifgr2.ifgr_name, ifg->ifgrq_group,
				    sizeof(ifgr2.ifgr_name));
				if (ioctl(s, SIOCGIFGMEMB, (caddr_t)&ifgr2) == 0)
					*answer = ifgr2.ifgr_len;
				else
					*answer = 0;

				item.key = strdup(ifg->ifgrq_group);
				item.data = answer;
				if (hsearch_r(item, ENTER, &ret_item,
					&isgroup_map) == 0)
					err(1, "interface group query response"
					    " map insert");
			}
		}
	}
	free(ifgr.ifgr_groups);
}