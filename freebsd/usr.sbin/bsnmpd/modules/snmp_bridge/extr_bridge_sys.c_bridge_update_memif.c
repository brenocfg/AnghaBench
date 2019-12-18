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
typedef  int uint32_t ;
struct mibif {int /*<<< orphan*/  index; } ;
struct ifbreq {int /*<<< orphan*/  ifbr_ifsname; int /*<<< orphan*/  ifbr_portno; } ;
struct ifbpstpreq {int /*<<< orphan*/  ifbr_ifsname; int /*<<< orphan*/  ifbr_portno; } ;
struct bridge_port {scalar_t__ status; int flags; int /*<<< orphan*/  port_no; } ;
struct bridge_if {int /*<<< orphan*/  ports_age; } ;
typedef  int int32_t ;

/* Variables and functions */
 int BP_FOUND ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ RowStatus_active ; 
 struct bridge_port* bridge_new_port (struct mibif*,struct bridge_if*) ; 
 struct bridge_port* bridge_port_bif_first (struct bridge_if*) ; 
 struct bridge_port* bridge_port_bif_next (struct bridge_port*) ; 
 int /*<<< orphan*/  bridge_port_clearinfo_opstp (struct bridge_port*) ; 
 struct bridge_port* bridge_port_find (int /*<<< orphan*/ ,struct bridge_if*) ; 
 struct ifbreq* bridge_port_find_ifstplist (int /*<<< orphan*/ ,struct ifbreq*,int) ; 
 int bridge_port_get_iflist (struct bridge_if*,struct ifbreq**) ; 
 int bridge_port_get_ifstplist (struct bridge_if*,struct ifbreq**) ; 
 int /*<<< orphan*/  bridge_port_getinfo_conf (struct ifbreq*,struct bridge_port*) ; 
 int /*<<< orphan*/  bridge_port_getinfo_mibif (struct mibif*,struct bridge_port*) ; 
 int /*<<< orphan*/  bridge_port_getinfo_opstp (struct ifbreq*,struct bridge_port*) ; 
 int /*<<< orphan*/  bridge_port_remove (struct bridge_port*,struct bridge_if*) ; 
 int /*<<< orphan*/  free (struct ifbreq*) ; 
 struct mibif* mib_find_if_sys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int
bridge_update_memif(struct bridge_if *bif)
{
	int added, updated;
	uint32_t i;
	int32_t buf_len;
	struct ifbreq *b_req_buf, *b_req;
	struct ifbpstpreq *bs_req_buf, *bs_req;
	struct bridge_port *bp, *bp_next;
	struct mibif *m_if;

	if ((buf_len = bridge_port_get_iflist(bif, &b_req_buf)) < 0)
		return (-1);

	added = updated = 0;

#define	BP_FOUND	0x01
	for (i = 0; i < buf_len / sizeof(struct ifbreq); i++) {
		b_req = b_req_buf + i;

		if ((m_if = mib_find_if_sys(b_req->ifbr_portno)) == NULL) {
			syslog(LOG_ERR, "bridge member %s not present "
			    "in mibII ifTable", b_req->ifbr_ifsname);
			continue;
		}

		if ((bp = bridge_port_find(m_if->index, bif)) == NULL &&
		    (bp = bridge_new_port(m_if, bif)) != NULL) {
			bp->status = RowStatus_active;
			added++;
		}

		if (bp != NULL) {
			updated++;
			bridge_port_getinfo_conf(b_req, bp);
			bridge_port_getinfo_mibif(m_if, bp);
			bp->flags |= BP_FOUND;
		}
	}
	free(b_req_buf);

	/* Clean up list. */
	for (bp = bridge_port_bif_first(bif); bp != NULL; bp = bp_next) {
		bp_next  = bridge_port_bif_next(bp);

		if ((bp->flags & BP_FOUND) == 0 &&
		    bp->status == RowStatus_active)
			bridge_port_remove(bp, bif);
		else
			bp->flags |= ~BP_FOUND;
	}
#undef	BP_FOUND

	if ((buf_len = bridge_port_get_ifstplist(bif, &bs_req_buf)) < 0)
		return (-1);

	for (bp = bridge_port_bif_first(bif); bp != NULL;
	    bp = bridge_port_bif_next(bp)) {
		if ((bs_req = bridge_port_find_ifstplist(bp->port_no,
		    bs_req_buf, buf_len)) == NULL)
			bridge_port_clearinfo_opstp(bp);
		else
			bridge_port_getinfo_opstp(bs_req, bp);
	}
	free(bs_req_buf);
	bif->ports_age = time(NULL);

	return (updated);
}