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
struct bridge_ports {int dummy; } ;
struct bridge_port {int /*<<< orphan*/  sysindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (struct bridge_ports*,struct bridge_port*,struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (struct bridge_ports*,struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_p ; 
 struct bridge_port* bridge_port_find_pos (struct bridge_ports*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_port_insert_at (struct bridge_ports*,struct bridge_port*,struct bridge_port**) ; 

__attribute__((used)) static void
bridge_port_memif_insert(struct bridge_ports *headp,
	struct bridge_port *bp, struct bridge_port **f_bp)
{
	struct bridge_port *temp;

	if (*f_bp != NULL)
		bridge_port_insert_at(headp, bp, f_bp);
	else {
		temp = bridge_port_find_pos(headp, bp->sysindex);

		if (temp == NULL)
			TAILQ_INSERT_HEAD(headp, bp, b_p);
		else
			TAILQ_INSERT_AFTER(headp, temp, bp, b_p);
		*f_bp = bp;
	}
}