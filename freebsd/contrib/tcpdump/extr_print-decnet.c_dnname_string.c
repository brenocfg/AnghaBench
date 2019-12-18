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
typedef  int /*<<< orphan*/  u_short ;
struct dn_naddr {int a_len; scalar_t__ a_addr; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 char* dnet_htoa (struct dn_naddr*) ; 
 char const* dnnum_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char const* strdup (char*) ; 

const char *
dnname_string(netdissect_options *ndo, u_short dnaddr)
{
#ifdef HAVE_DNET_HTOA
	struct dn_naddr dna;
	char *dnname;

	dna.a_len = sizeof(short);
	memcpy((char *)dna.a_addr, (char *)&dnaddr, sizeof(short));
	dnname = dnet_htoa(&dna);
	if(dnname != NULL)
		return (strdup(dnname));
	else
		return(dnnum_string(ndo, dnaddr));
#else
	return(dnnum_string(ndo, dnaddr));	/* punt */
#endif
}