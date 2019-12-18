#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TTEST_16BITS (int const*) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  ppp_ml_flag_values ; 

__attribute__((used)) static void
handle_mlppp(netdissect_options *ndo,
             const u_char *p, int length)
{
    if (!ndo->ndo_eflag)
        ND_PRINT((ndo, "MLPPP, "));

    if (length < 2) {
        ND_PRINT((ndo, "[|mlppp]"));
        return;
    }
    if (!ND_TTEST_16BITS(p)) {
        ND_PRINT((ndo, "[|mlppp]"));
        return;
    }

    ND_PRINT((ndo, "seq 0x%03x, Flags [%s], length %u",
           (EXTRACT_16BITS(p))&0x0fff, /* only support 12-Bit sequence space for now */
           bittok2str(ppp_ml_flag_values, "none", *p & 0xc0),
           length));
}