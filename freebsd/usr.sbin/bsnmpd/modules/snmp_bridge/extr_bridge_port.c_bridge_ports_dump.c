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
struct bridge_port {int /*<<< orphan*/  port_no; int /*<<< orphan*/  p_name; } ;
struct bridge_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 struct bridge_port* bridge_port_bif_first (struct bridge_if*) ; 
 struct bridge_port* bridge_port_bif_next (struct bridge_port*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bridge_ports_dump(struct bridge_if *bif)
{
	struct bridge_port *bp;

	for (bp = bridge_port_bif_first(bif); bp != NULL;
	    bp = bridge_port_bif_next(bp)) {
		syslog(LOG_ERR, "memif - %s, index - %d",
		bp->p_name, bp->port_no);
	}
}