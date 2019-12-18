#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pim {int /*<<< orphan*/  pim_typever; int /*<<< orphan*/  pim_rsv; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIM_TYPE (int /*<<< orphan*/ ) ; 
 int PIM_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pimv2_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pimv2_type_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
pim_print(netdissect_options *ndo,
          register const u_char *bp, register u_int len, const u_char *bp2)
{
	register const struct pim *pim = (const struct pim *)bp;

#ifdef notyet			/* currently we see only version and type */
	ND_TCHECK(pim->pim_rsv);
#endif

	ND_TCHECK(pim->pim_typever);
	switch (PIM_VER(pim->pim_typever)) {
	case 2:
		if (!ndo->ndo_vflag) {
			ND_PRINT((ndo, "PIMv%u, %s, length %u",
			          PIM_VER(pim->pim_typever),
			          tok2str(pimv2_type_values,"Unknown Type",PIM_TYPE(pim->pim_typever)),
			          len));
			return;
		} else {
			ND_PRINT((ndo, "PIMv%u, length %u\n\t%s",
			          PIM_VER(pim->pim_typever),
			          len,
			          tok2str(pimv2_type_values,"Unknown Type",PIM_TYPE(pim->pim_typever))));
			pimv2_print(ndo, bp, len, bp2);
		}
		break;
	default:
		ND_PRINT((ndo, "PIMv%u, length %u",
		          PIM_VER(pim->pim_typever),
		          len));
		break;
	}
	return;

trunc:
	ND_PRINT((ndo, "[|pim]"));
	return;
}