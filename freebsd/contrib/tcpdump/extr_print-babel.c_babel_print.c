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
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  babel_print_v2 (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

void
babel_print(netdissect_options *ndo,
            const u_char *cp, u_int length)
{
    ND_PRINT((ndo, "babel"));

    ND_TCHECK2(*cp, 4);

    if(cp[0] != 42) {
        ND_PRINT((ndo, " invalid header"));
        return;
    } else {
        ND_PRINT((ndo, " %d", cp[1]));
    }

    switch(cp[1]) {
    case 2:
        babel_print_v2(ndo, cp, length);
        break;
    default:
        ND_PRINT((ndo, " unknown version"));
        break;
    }

    return;

 trunc:
    ND_PRINT((ndo, " %s", tstr));
    return;
}