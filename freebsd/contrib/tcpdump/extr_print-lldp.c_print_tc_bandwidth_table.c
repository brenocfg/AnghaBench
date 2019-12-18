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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_tc_bandwidth_table(netdissect_options *ndo,
                         const u_char *ptr)
{
    ND_PRINT((ndo, "\n\t    TC Bandwidth Table"));
    ND_PRINT((ndo, "\n\t     TC%%   : 0   1   2   3   4   5   6   7"));
    ND_PRINT((ndo, "\n\t     Value : %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d",
             ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7]));
}