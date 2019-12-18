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
struct pfctl_altq {int dummy; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_4__ {char* key; struct pfctl_altq* data; } ;
typedef  TYPE_1__ ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 int IFNAMSIZ ; 
 int PF_QNAME_SIZE ; 
 scalar_t__ hsearch_r (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_map ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static struct pfctl_altq *
qname_to_pfaltq(const char *qname, const char *ifname)
{
	ENTRY	 item;
	ENTRY	*ret_item;
	char	 key[IFNAMSIZ + PF_QNAME_SIZE];

	item.key = key;
	snprintf(item.key, sizeof(key), "%s:%s", ifname, qname);
	if (hsearch_r(item, FIND, &ret_item, &queue_map) == 0)
		return (NULL);

	return (ret_item->data);
}