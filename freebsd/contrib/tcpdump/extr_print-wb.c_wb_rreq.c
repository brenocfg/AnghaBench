#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  p_uid; int /*<<< orphan*/  p_sid; } ;
struct pkt_rreq {int /*<<< orphan*/  pr_eseq; int /*<<< orphan*/  pr_sseq; TYPE_1__ pr_page; int /*<<< orphan*/  pr_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST (struct pkt_rreq const) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wb_rreq(netdissect_options *ndo,
        const struct pkt_rreq *rreq, u_int len)
{
	ND_PRINT((ndo, " wb-rreq:"));
	if (len < sizeof(*rreq) || !ND_TTEST(*rreq))
		return (-1);

	ND_PRINT((ndo, " please repair %s %s:%u<%u:%u>",
	       ipaddr_string(ndo, &rreq->pr_id),
	       ipaddr_string(ndo, &rreq->pr_page.p_sid),
	       EXTRACT_32BITS(&rreq->pr_page.p_uid),
	       EXTRACT_32BITS(&rreq->pr_sseq),
	       EXTRACT_32BITS(&rreq->pr_eseq)));
	return (0);
}