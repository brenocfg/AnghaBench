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

/* Variables and functions */
 int ND_EXAUTHSYS ; 
 int ND_EXGSS ; 
 int ND_EXGSSINTEGRITY ; 
 int ND_EXGSSPRIVACY ; 
 int ND_GSS ; 
 int ND_GSSINTEGRITY ; 
 int ND_GSSPRIVACY ; 

int
nfsd_checkrootexp(struct nfsrv_descript *nd)
{

	if ((nd->nd_flag & (ND_GSS | ND_EXAUTHSYS)) == ND_EXAUTHSYS)
		return (0);
	if ((nd->nd_flag & (ND_GSSINTEGRITY | ND_EXGSSINTEGRITY)) ==
	    (ND_GSSINTEGRITY | ND_EXGSSINTEGRITY))
		return (0);
	if ((nd->nd_flag & (ND_GSSPRIVACY | ND_EXGSSPRIVACY)) ==
	    (ND_GSSPRIVACY | ND_EXGSSPRIVACY))
		return (0);
	if ((nd->nd_flag & (ND_GSS | ND_GSSINTEGRITY | ND_GSSPRIVACY |
	     ND_EXGSS)) == (ND_GSS | ND_EXGSS))
		return (0);
	return (1);
}