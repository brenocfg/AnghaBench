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
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int GRE_VERS_MASK ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  gre_print_0 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  gre_print_1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tstr ; 

void
gre_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	u_int len = length, vers;

	ND_TCHECK2(*bp, 2);
	if (len < 2)
		goto trunc;
	vers = EXTRACT_16BITS(bp) & GRE_VERS_MASK;
        ND_PRINT((ndo, "GREv%u",vers));

        switch(vers) {
        case 0:
            gre_print_0(ndo, bp, len);
            break;
        case 1:
            gre_print_1(ndo, bp, len);
            break;
	default:
            ND_PRINT((ndo, " ERROR: unknown-version"));
            break;
        }
        return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return;
}