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
struct bridge_port {scalar_t__ sysindex; scalar_t__ if_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct bridge_port*,struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct bridge_ports*,struct bridge_port*,int /*<<< orphan*/ ) ; 
 struct bridge_port* TAILQ_NEXT (struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_p ; 

__attribute__((used)) static void
bridge_port_insert_at(struct bridge_ports *headp,
	struct bridge_port *bp, struct bridge_port **f_bp)
{
	struct bridge_port *t1;

	assert(f_bp != NULL);

	for (t1 = *f_bp;
	    t1 != NULL && bp->sysindex == t1->sysindex;
	    t1 = TAILQ_NEXT(t1, b_p)) {
		if (bp->if_idx < t1->if_idx) {
			TAILQ_INSERT_BEFORE(t1, bp, b_p);
			if (*f_bp == t1)
				*f_bp = bp;
			return;
		}
	}

	/*
	 * Handle the case when our first port was actually the
	 * last element of the TAILQ.
	 */
	if (t1 == NULL)
		TAILQ_INSERT_TAIL(headp, bp, b_p);
	else
		TAILQ_INSERT_BEFORE(t1, bp, b_p);
}