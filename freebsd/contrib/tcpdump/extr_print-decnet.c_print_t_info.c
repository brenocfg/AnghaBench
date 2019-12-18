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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int TI_BLOCK ; 
#define  TI_ENDNODE 130 
#define  TI_L1ROUT 129 
#define  TI_L2ROUT 128 
 int TI_VERIF ; 

__attribute__((used)) static void
print_t_info(netdissect_options *ndo,
             int info)
{
	int ntype = info & 3;
	switch (ntype) {
	case 0: ND_PRINT((ndo, "reserved-ntype? ")); break;
	case TI_L2ROUT: ND_PRINT((ndo, "l2rout ")); break;
	case TI_L1ROUT: ND_PRINT((ndo, "l1rout ")); break;
	case TI_ENDNODE: ND_PRINT((ndo, "endnode ")); break;
	}
	if (info & TI_VERIF)
	    ND_PRINT((ndo, "verif "));
	if (info & TI_BLOCK)
	    ND_PRINT((ndo, "blo "));
}