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
 int II_BLOCK ; 
#define  II_ENDNODE 130 
#define  II_L1ROUT 129 
#define  II_L2ROUT 128 
 int II_NOMCAST ; 
 int II_TYPEMASK ; 
 int II_VERIF ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_i_info(netdissect_options *ndo,
             int info)
{
	int ntype = info & II_TYPEMASK;
	switch (ntype) {
	case 0: ND_PRINT((ndo, "reserved-ntype? ")); break;
	case II_L2ROUT: ND_PRINT((ndo, "l2rout ")); break;
	case II_L1ROUT: ND_PRINT((ndo, "l1rout ")); break;
	case II_ENDNODE: ND_PRINT((ndo, "endnode ")); break;
	}
	if (info & II_VERIF)
	    ND_PRINT((ndo, "verif "));
	if (info & II_NOMCAST)
	    ND_PRINT((ndo, "nomcast "));
	if (info & II_BLOCK)
	    ND_PRINT((ndo, "blo "));
}