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
struct mibif {int /*<<< orphan*/  name; int /*<<< orphan*/  sysindex; int /*<<< orphan*/  index; } ;
struct bridge_port {int /*<<< orphan*/  admin_ptp; void* oper_ptp; void* oper_edge; void* admin_edge; void* proto_migr; int /*<<< orphan*/  circuit; int /*<<< orphan*/  p_name; int /*<<< orphan*/  port_no; int /*<<< orphan*/  if_idx; int /*<<< orphan*/  sysindex; } ;
struct bridge_if {int /*<<< orphan*/  f_bp; int /*<<< orphan*/  sysindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  StpPortAdminPointToPointType_auto ; 
 void* TruthValue_false ; 
 int /*<<< orphan*/  bridge_port_memif_insert (int /*<<< orphan*/ *,struct bridge_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bridge_ports ; 
 int /*<<< orphan*/  bzero (struct bridge_port*,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  oid_zeroDotZero ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct bridge_port *
bridge_new_port(struct mibif *mif, struct bridge_if *bif)
{
	struct bridge_port *bp;

	if ((bp = (struct bridge_port *) malloc(sizeof(*bp))) == NULL) {
		syslog(LOG_ERR, "bridge new member: failed: %s",
			strerror(errno));
		return (NULL);
	}

	bzero(bp, sizeof(*bp));

	bp->sysindex = bif->sysindex;
	bp->if_idx = mif->index;
	bp->port_no = mif->sysindex;
	strlcpy(bp->p_name, mif->name, IFNAMSIZ);
	bp->circuit = oid_zeroDotZero;

	/*
	 * Initialize all rstpMib specific values to false/default.
	 * These will be set to their true values later if the bridge
	 * supports RSTP.
	 */
	bp->proto_migr = TruthValue_false;
	bp->admin_edge = TruthValue_false;
	bp->oper_edge = TruthValue_false;
	bp->oper_ptp = TruthValue_false;
	bp->admin_ptp = StpPortAdminPointToPointType_auto;

	bridge_port_memif_insert(&bridge_ports, bp, &(bif->f_bp));

	return (bp);
}