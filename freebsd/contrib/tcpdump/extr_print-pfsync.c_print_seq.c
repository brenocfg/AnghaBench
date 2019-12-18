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
struct pfsync_state_peer {scalar_t__ seqlo; scalar_t__ seqhi; scalar_t__ seqdiff; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohl (scalar_t__) ; 

__attribute__((used)) static void
print_seq(netdissect_options *ndo, const struct pfsync_state_peer *p)
{
	if (p->seqdiff)
		ND_PRINT((ndo, "[%u + %u](+%u)", ntohl(p->seqlo),
		    ntohl(p->seqhi) - ntohl(p->seqlo), ntohl(p->seqdiff)));
	else
		ND_PRINT((ndo, "[%u + %u]", ntohl(p->seqlo),
		    ntohl(p->seqhi) - ntohl(p->seqlo)));
}