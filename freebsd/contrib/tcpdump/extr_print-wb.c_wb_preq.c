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
struct pkt_preq {TYPE_1__ pp_page; int /*<<< orphan*/  pp_low; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST (struct pkt_preq const) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wb_preq(netdissect_options *ndo,
        const struct pkt_preq *preq, u_int len)
{
	ND_PRINT((ndo, " wb-preq:"));
	if (len < sizeof(*preq) || !ND_TTEST(*preq))
		return (-1);

	ND_PRINT((ndo, " need %u/%s:%u",
	       EXTRACT_32BITS(&preq->pp_low),
	       ipaddr_string(ndo, &preq->pp_page.p_sid),
	       EXTRACT_32BITS(&preq->pp_page.p_uid)));
	return (0);
}