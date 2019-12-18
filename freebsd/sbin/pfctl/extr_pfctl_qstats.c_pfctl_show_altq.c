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
struct TYPE_2__ {int local_flags; int /*<<< orphan*/  ifname; } ;
struct pf_altq_node {TYPE_1__ altq; struct pf_altq_node* next; } ;

/* Variables and functions */
 int PFALTQ_FLAG_IF_REMOVED ; 
 int PF_OPT_SHOWALL ; 
 int /*<<< orphan*/  STAT_INTERVAL ; 
 int /*<<< orphan*/  altqsupport ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfctl_free_altq_node (struct pf_altq_node*) ; 
 int /*<<< orphan*/  pfctl_print_altq_node (int,struct pf_altq_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int pfctl_update_qstats (int,struct pf_altq_node**) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
pfctl_show_altq(int dev, const char *iface, int opts, int verbose2)
{
	struct pf_altq_node	*root = NULL, *node;
	int			 nodes, dotitle = (opts & PF_OPT_SHOWALL);

#ifdef __FreeBSD__
	if (!altqsupport)
		return (-1);
#endif

	if ((nodes = pfctl_update_qstats(dev, &root)) < 0)
		return (-1);

	if (nodes == 0)
		printf("No queue in use\n");
	for (node = root; node != NULL; node = node->next) {
		if (iface != NULL && strcmp(node->altq.ifname, iface))
			continue;
		if (dotitle) {
			pfctl_print_title("ALTQ:");
			dotitle = 0;
		}
		pfctl_print_altq_node(dev, node, 0, opts);
	}

	while (verbose2 && nodes > 0) {
		printf("\n");
		fflush(stdout);
		sleep(STAT_INTERVAL);
		if ((nodes = pfctl_update_qstats(dev, &root)) == -1)
			return (-1);
		for (node = root; node != NULL; node = node->next) {
			if (iface != NULL && strcmp(node->altq.ifname, iface))
				continue;
#ifdef __FreeBSD__
			if (node->altq.local_flags & PFALTQ_FLAG_IF_REMOVED)
				continue;
#endif
			pfctl_print_altq_node(dev, node, 0, opts);
		}
	}
	pfctl_free_altq_node(root);
	return (0);
}