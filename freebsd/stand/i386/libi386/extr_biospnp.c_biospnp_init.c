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
struct pnp_isaConfiguration {int ic_revision; int ic_rdport; int /*<<< orphan*/  ic_nCSN; } ;
struct pnp_ICstructure {int dummy; } ;

/* Variables and functions */
#define  PNP_FUNCTION_NOT_SUPPORTED 129 
#define  PNP_SUCCESS 128 
 char* PTOV (int) ; 
 int /*<<< orphan*/  bcmp (char*,char*,int) ; 
 int biospnp_f00 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int biospnp_f40 (int /*<<< orphan*/ ) ; 
 int isapnp_readport ; 
 struct pnp_ICstructure* pnp_Icheck ; 
 struct pnp_isaConfiguration pnp_NodeSize ; 
 struct pnp_isaConfiguration pnp_NumNodes ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vsegofs (struct pnp_isaConfiguration*) ; 

__attribute__((used)) static int
biospnp_init(void)
{
    struct pnp_isaConfiguration	icfg;
    char			*sigptr;
    int				result;
    
    /* Search for the $PnP signature */
    pnp_Icheck = NULL;
    for (sigptr = PTOV(0xf0000); sigptr < PTOV(0xfffff); sigptr += 16)
	if (!bcmp(sigptr, "$PnP", 4)) {
	    pnp_Icheck = (struct pnp_ICstructure *)sigptr;
	    break;
	}
	
    /* No signature, no BIOS */
    if (pnp_Icheck == NULL)
	return(1);

    /*
     * Fetch the system table parameters as a test of the BIOS
     */
    result = biospnp_f00(vsegofs(&pnp_NumNodes), vsegofs(&pnp_NodeSize));
    if (result != PNP_SUCCESS) {
	return(1);
    }

    /*
     * Look for the PnP ISA configuration table 
     */
    result = biospnp_f40(vsegofs(&icfg));
    switch (result) {
    case PNP_SUCCESS:
	/* If the BIOS found some PnP devices, take its hint for the read port */
	if ((icfg.ic_revision == 1) && (icfg.ic_nCSN > 0))
	    isapnp_readport = icfg.ic_rdport;
	break;
    case PNP_FUNCTION_NOT_SUPPORTED:
	/* The BIOS says there is no ISA bus (should we trust that this works?) */
	printf("PnP BIOS claims no ISA bus\n");
	isapnp_readport = -1;
	break;
    }
    return(0);
}