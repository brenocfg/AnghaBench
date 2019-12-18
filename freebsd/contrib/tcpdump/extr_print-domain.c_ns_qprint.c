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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int C_IN ; 
 int C_QU ; 
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ns_class2str ; 
 int /*<<< orphan*/ * ns_nprint (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ns_nskip (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ns_type2str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static const u_char *
ns_qprint(netdissect_options *ndo,
          register const u_char *cp, register const u_char *bp, int is_mdns)
{
	register const u_char *np = cp;
	register u_int i, class;

	cp = ns_nskip(ndo, cp);

	if (cp == NULL || !ND_TTEST2(*cp, 4))
		return(NULL);

	/* print the qtype */
	i = EXTRACT_16BITS(cp);
	cp += 2;
	ND_PRINT((ndo, " %s", tok2str(ns_type2str, "Type%d", i)));
	/* print the qclass (if it's not IN) */
	i = EXTRACT_16BITS(cp);
	cp += 2;
	if (is_mdns)
		class = (i & ~C_QU);
	else
		class = i;
	if (class != C_IN)
		ND_PRINT((ndo, " %s", tok2str(ns_class2str, "(Class %d)", class)));
	if (is_mdns) {
		ND_PRINT((ndo, i & C_QU ? " (QU)" : " (QM)"));
	}

	ND_PRINT((ndo, "? "));
	cp = ns_nprint(ndo, np, bp);
	return(cp ? cp + 4 : NULL);
}