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
struct wds {struct wds* next; int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  free (struct wds*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct wds* wds ; 

__attribute__((used)) static void
wds_destroy(const char *ifname)
{
	struct wds *p, **pp;

	for (pp = &wds; (p = *pp) != NULL; pp = &p->next)
		if (strncmp(p->ifname, ifname, IFNAMSIZ) == 0)
			break;
	if (p != NULL) {
		*pp = p->next;
		/* NB: vap already destroyed */
		free(p);
		return;
	}
}