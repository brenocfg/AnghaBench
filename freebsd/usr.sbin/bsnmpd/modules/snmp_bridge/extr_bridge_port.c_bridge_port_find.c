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
struct bridge_port {scalar_t__ sysindex; scalar_t__ if_idx; } ;
struct bridge_if {scalar_t__ sysindex; struct bridge_port* f_bp; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 struct bridge_port* TAILQ_NEXT (struct bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_p ; 

struct bridge_port *
bridge_port_find(int32_t if_idx, struct bridge_if *bif)
{
	struct bridge_port *bp;

	for (bp = bif->f_bp; bp != NULL; bp = TAILQ_NEXT(bp, b_p)) {
		if (bp->sysindex != bif->sysindex) {
			bp = NULL;
			break;
		}

		if (bp->if_idx == if_idx)
			break;
	}

	return (bp);
}