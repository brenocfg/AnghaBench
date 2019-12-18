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
typedef  scalar_t__ uint32_t ;
struct pfloghdr {scalar_t__ uid; int /*<<< orphan*/  ifname; int /*<<< orphan*/  dir; int /*<<< orphan*/  action; int /*<<< orphan*/  reason; int /*<<< orphan*/  ruleset; int /*<<< orphan*/  subrulenr; int /*<<< orphan*/  rulenr; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ UID_MAX ; 
 int /*<<< orphan*/  pf_actions ; 
 int /*<<< orphan*/  pf_directions ; 
 int /*<<< orphan*/  pf_reasons ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pflog_print(netdissect_options *ndo, const struct pfloghdr *hdr)
{
	uint32_t rulenr, subrulenr;

	rulenr = EXTRACT_32BITS(&hdr->rulenr);
	subrulenr = EXTRACT_32BITS(&hdr->subrulenr);
	if (subrulenr == (uint32_t)-1)
		ND_PRINT((ndo, "rule %u/", rulenr));
	else
		ND_PRINT((ndo, "rule %u.%s.%u/", rulenr, hdr->ruleset, subrulenr));

	ND_PRINT((ndo, "%s", tok2str(pf_reasons, "unkn(%u)", hdr->reason)));

	if (hdr->uid != UID_MAX)
		ND_PRINT((ndo, " [uid %u]", (unsigned)hdr->uid));

	ND_PRINT((ndo, ": %s %s on %s: ",
	    tok2str(pf_actions, "unkn(%u)", hdr->action),
	    tok2str(pf_directions, "unkn(%u)", hdr->dir),
	    hdr->ifname));
}