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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct aodv_rrep6_draft_01 {int rrep_type; int rrep_ps; int /*<<< orphan*/  rrep_life; int /*<<< orphan*/  rrep_oa; int /*<<< orphan*/  rrep_ds; int /*<<< orphan*/  rrep_da; int /*<<< orphan*/  rrep_hops; } ;
struct aodv_ext {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct aodv_rrep6_draft_01 const) ; 
 int RREP_ACK ; 
 int RREP_PREFIX_MASK ; 
 int RREP_REPAIR ; 
 int /*<<< orphan*/  aodv_extension (int /*<<< orphan*/ *,struct aodv_ext const*,int) ; 
 int /*<<< orphan*/  ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aodv_v6_draft_01_rrep(netdissect_options *ndo, const u_char *dat, u_int length)
{
	u_int i;
	const struct aodv_rrep6_draft_01 *ap = (const struct aodv_rrep6_draft_01 *)dat;

	ND_TCHECK(*ap);
	if (length < sizeof(*ap))
		goto trunc;
	ND_PRINT((ndo, " rrep %u %s%sprefix %u hops %u\n"
	   "\tdst %s dseq %lu src %s %lu ms", length,
	    ap->rrep_type & RREP_REPAIR ? "[R]" : "",
	    ap->rrep_type & RREP_ACK ? "[A] " : " ",
	    ap->rrep_ps & RREP_PREFIX_MASK,
	    ap->rrep_hops,
	    ip6addr_string(ndo, &ap->rrep_da),
	    (unsigned long)EXTRACT_32BITS(&ap->rrep_ds),
	    ip6addr_string(ndo, &ap->rrep_oa),
	    (unsigned long)EXTRACT_32BITS(&ap->rrep_life)));
	i = length - sizeof(*ap);
	if (i >= sizeof(struct aodv_ext))
		aodv_extension(ndo, (const struct aodv_ext *)(dat + sizeof(*ap)), i);
	return;

trunc:
	ND_PRINT((ndo, " [|rreq"));
}