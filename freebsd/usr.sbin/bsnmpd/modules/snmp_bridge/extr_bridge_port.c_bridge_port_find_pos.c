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
typedef  scalar_t__ uint32_t ;
struct bridge_ports {int dummy; } ;
struct bridge_port {scalar_t__ sysindex; } ;

/* Variables and functions */
 struct bridge_port* TAILQ_FIRST (struct bridge_ports*) ; 
 struct bridge_port* TAILQ_LAST (struct bridge_ports*,int /*<<< orphan*/ ) ; 
 struct bridge_port* TAILQ_NEXT (struct bridge_port*,int /*<<< orphan*/ ) ; 
 struct bridge_port* TAILQ_PREV (struct bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_p ; 
 scalar_t__ bridge_compare_sysidx (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bridge_ports ; 

__attribute__((used)) static struct bridge_port *
bridge_port_find_pos(struct bridge_ports *headp, uint32_t b_idx)
{
	uint32_t t_idx;
	struct bridge_port *t1;

	if ((t1 = TAILQ_FIRST(headp)) == NULL ||
	    bridge_compare_sysidx(b_idx, t1->sysindex) < 0)
		return (NULL);

	t_idx = t1->sysindex;

	for (t1 = TAILQ_NEXT(t1, b_p); t1 != NULL; t1 = TAILQ_NEXT(t1, b_p)) {
		if (t1->sysindex != t_idx) {
			if (bridge_compare_sysidx(b_idx, t1->sysindex) < 0)
				return (TAILQ_PREV(t1, bridge_ports, b_p));
			else
				t_idx = t1->sysindex;
		}
	}

	if (t1 == NULL)
		t1 = TAILQ_LAST(headp, bridge_ports);

	return (t1);
}