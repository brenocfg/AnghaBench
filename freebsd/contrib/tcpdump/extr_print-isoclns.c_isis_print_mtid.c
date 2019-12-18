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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ISIS_MASK_MTFLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISIS_MASK_MTID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isis_mt_flag_values ; 
 int /*<<< orphan*/  isis_mt_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isis_print_mtid(netdissect_options *ndo,
                const uint8_t *tptr, const char *ident)
{
    if (!ND_TTEST2(*tptr, 2))
        return(0);

    ND_PRINT((ndo, "%s%s",
           ident,
           tok2str(isis_mt_values,
                   "Reserved for IETF Consensus",
                   ISIS_MASK_MTID(EXTRACT_16BITS(tptr)))));

    ND_PRINT((ndo, " Topology (0x%03x), Flags: [%s]",
           ISIS_MASK_MTID(EXTRACT_16BITS(tptr)),
           bittok2str(isis_mt_flag_values, "none",ISIS_MASK_MTFLAGS(EXTRACT_16BITS(tptr)))));

    return(2);
}