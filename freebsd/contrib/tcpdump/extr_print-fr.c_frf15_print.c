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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int const FR_FRF15_FRAGTYPE ; 
 int const MFR_BEC_MASK ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  frf_flag_values ; 

__attribute__((used)) static void
frf15_print(netdissect_options *ndo,
            const u_char *p, u_int length)
{
    uint16_t sequence_num, flags;

    if (length < 2)
        goto trunc;
    ND_TCHECK2(*p, 2);

    flags = p[0]&MFR_BEC_MASK;
    sequence_num = (p[0]&0x1e)<<7 | p[1];

    ND_PRINT((ndo, "FRF.15, seq 0x%03x, Flags [%s],%s Fragmentation, length %u",
           sequence_num,
           bittok2str(frf_flag_values,"none",flags),
           p[0]&FR_FRF15_FRAGTYPE ? "Interface" : "End-to-End",
           length));

/* TODO:
 * depending on all permutations of the B, E and C bit
 * dig as deep as we can - e.g. on the first (B) fragment
 * there is enough payload to print the IP header
 * on non (B) fragments it depends if the fragmentation
 * model is end-to-end or interface based wether we want to print
 * another Q.922 header
 */
    return;

trunc:
    ND_PRINT((ndo, "[|frf.15]"));
}