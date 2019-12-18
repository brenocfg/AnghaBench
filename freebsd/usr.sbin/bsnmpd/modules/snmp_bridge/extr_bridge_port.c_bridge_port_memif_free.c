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
struct bridge_port {scalar_t__ sysindex; } ;
struct bridge_if {scalar_t__ sysindex; struct bridge_port* f_bp; } ;

/* Variables and functions */
 struct bridge_port* TAILQ_NEXT (struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct bridge_ports*,struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_p ; 
 int /*<<< orphan*/  free (struct bridge_port*) ; 

__attribute__((used)) static void
bridge_port_memif_free(struct bridge_ports *headp,
	struct bridge_if *bif)
{
	struct bridge_port *bp;

	while (bif->f_bp != NULL && bif->sysindex == bif->f_bp->sysindex) {
		bp = TAILQ_NEXT(bif->f_bp, b_p);
		TAILQ_REMOVE(headp, bif->f_bp, b_p);
		free(bif->f_bp);
		bif->f_bp = bp;
	}
}