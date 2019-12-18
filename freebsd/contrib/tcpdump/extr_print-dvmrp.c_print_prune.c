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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  unsigned_relts_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_prune(netdissect_options *ndo,
            register const u_char *bp)
{
	ND_TCHECK2(bp[0], 12);
	ND_PRINT((ndo, " src %s grp %s", ipaddr_string(ndo, bp), ipaddr_string(ndo, bp + 4)));
	bp += 8;
	ND_PRINT((ndo, " timer "));
	unsigned_relts_print(ndo, EXTRACT_32BITS(bp));
	return (0);
trunc:
	return (-1);
}