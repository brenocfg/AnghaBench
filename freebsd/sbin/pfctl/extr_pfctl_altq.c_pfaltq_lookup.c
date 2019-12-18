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
struct TYPE_4__ {char* key; struct pfctl_altq* data; } ;
typedef  TYPE_1__ ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 scalar_t__ hsearch_r (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_map ; 

__attribute__((used)) static struct pfctl_altq *
pfaltq_lookup(char *ifname)
{
	ENTRY	 item;
	ENTRY	*ret_item;

	item.key = ifname;
	if (hsearch_r(item, FIND, &ret_item, &if_map) == 0)
		return (NULL);

	return (ret_item->data);
}