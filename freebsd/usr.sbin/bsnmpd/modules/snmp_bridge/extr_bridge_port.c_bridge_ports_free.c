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
struct bridge_port {int dummy; } ;

/* Variables and functions */
 struct bridge_port* TAILQ_FIRST (struct bridge_ports*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct bridge_ports*,struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_p ; 
 int /*<<< orphan*/  free (struct bridge_port*) ; 

__attribute__((used)) static void
bridge_ports_free(struct bridge_ports *headp)
{
	struct bridge_port *bp;

	while ((bp = TAILQ_FIRST(headp)) != NULL) {
		TAILQ_REMOVE(headp, bp, b_p);
		free(bp);
	}
}