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
typedef  int /*<<< orphan*/  u_char ;
struct msnlb_heartbeat_pkt {int /*<<< orphan*/  host_ip; int /*<<< orphan*/  virtual_ip; int /*<<< orphan*/  host_prio; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_LE_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct msnlb_heartbeat_pkt const) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
msnlb_print(netdissect_options *ndo, const u_char *bp)
{
	const struct msnlb_heartbeat_pkt *hb;

	hb = (const struct msnlb_heartbeat_pkt *)bp;
	ND_TCHECK(*hb);

	ND_PRINT((ndo, "MS NLB heartbeat, host priority: %u,",
		EXTRACT_LE_32BITS(&(hb->host_prio))));
	ND_PRINT((ndo, " cluster IP: %s,", ipaddr_string(ndo, &(hb->virtual_ip))));
	ND_PRINT((ndo, " host IP: %s", ipaddr_string(ndo, &(hb->host_ip))));
	return;
trunc:
	ND_PRINT((ndo, "[|MS NLB]"));
}