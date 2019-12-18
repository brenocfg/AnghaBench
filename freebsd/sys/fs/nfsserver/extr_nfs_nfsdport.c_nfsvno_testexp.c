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
struct nfsrv_descript {int nd_flag; } ;
struct nfsexstuff {int nes_numsecflavor; scalar_t__* nes_secflavors; } ;

/* Variables and functions */
 scalar_t__ AUTH_SYS ; 
 int ND_GSS ; 
 int ND_GSSINTEGRITY ; 
 int ND_GSSPRIVACY ; 
 scalar_t__ RPCSEC_GSS_KRB5 ; 
 scalar_t__ RPCSEC_GSS_KRB5I ; 
 scalar_t__ RPCSEC_GSS_KRB5P ; 

int
nfsvno_testexp(struct nfsrv_descript *nd, struct nfsexstuff *exp)
{
	int i;

	/*
	 * This seems odd, but allow the case where the security flavor
	 * list is empty. This happens when NFSv4 is traversing non-exported
	 * file systems. Exported file systems should always have a non-empty
	 * security flavor list.
	 */
	if (exp->nes_numsecflavor == 0)
		return (0);

	for (i = 0; i < exp->nes_numsecflavor; i++) {
		/*
		 * The tests for privacy and integrity must be first,
		 * since ND_GSS is set for everything but AUTH_SYS.
		 */
		if (exp->nes_secflavors[i] == RPCSEC_GSS_KRB5P &&
		    (nd->nd_flag & ND_GSSPRIVACY))
			return (0);
		if (exp->nes_secflavors[i] == RPCSEC_GSS_KRB5I &&
		    (nd->nd_flag & ND_GSSINTEGRITY))
			return (0);
		if (exp->nes_secflavors[i] == RPCSEC_GSS_KRB5 &&
		    (nd->nd_flag & ND_GSS))
			return (0);
		if (exp->nes_secflavors[i] == AUTH_SYS &&
		    (nd->nd_flag & ND_GSS) == 0)
			return (0);
	}
	return (1);
}