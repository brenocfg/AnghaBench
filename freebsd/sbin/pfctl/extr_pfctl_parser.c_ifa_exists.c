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
struct node_host {scalar_t__ af; int /*<<< orphan*/ * ifname; struct node_host* next; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 struct node_host* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int get_query_socket () ; 
 int /*<<< orphan*/  ifa_load () ; 
 struct node_host* iftab ; 
 scalar_t__ is_a_group (char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

struct node_host *
ifa_exists(char *ifa_name)
{
	struct node_host	*n;
	int			s;

	if (iftab == NULL)
		ifa_load();

	/* check whether this is a group */
	s = get_query_socket();
	if (is_a_group(ifa_name)) {
		/* fake a node_host */
		if ((n = calloc(1, sizeof(*n))) == NULL)
			err(1, "calloc");
		if ((n->ifname = strdup(ifa_name)) == NULL)
			err(1, "strdup");
		return (n);
	}

	for (n = iftab; n; n = n->next) {
		if (n->af == AF_LINK && !strncmp(n->ifname, ifa_name, IFNAMSIZ))
			return (n);
	}

	return (NULL);
}