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
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
typedef  size_t u_int ;
struct pnpinfo {char* pi_desc; } ;
struct pnp_devNode {size_t* dn_data; size_t dn_size; } ;

/* Variables and functions */
#define  COMP_DEVICE_ID 130 
#define  END_TAG 129 
#define  ID_STRING_ANSI 128 
 int PNP_LRES_NUM (size_t) ; 
 scalar_t__ PNP_RES_TYPE (size_t) ; 
 size_t PNP_SRES_LEN (size_t) ; 
 int PNP_SRES_NUM (size_t) ; 
 int /*<<< orphan*/  bcopy (size_t*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  pnp_addident (struct pnpinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_eisaformat (size_t*) ; 

__attribute__((used)) static void
biospnp_scanresdata(struct pnpinfo *pi, struct pnp_devNode *dn)
{
    u_int	tag, i, rlen, dlen;
    uint8_t	*p;
    char	*str;

    p = dn->dn_data;			/* point to resource data */
    dlen = dn->dn_size - (p - (uint8_t *)dn);	/* length of resource data */

    for (i = 0; i < dlen; i+= rlen) {
	tag = p[i];
	i++;
	if (PNP_RES_TYPE(tag) == 0) {
	    rlen = PNP_SRES_LEN(tag);
	    /* small resource */
	    switch (PNP_SRES_NUM(tag)) {

	    case COMP_DEVICE_ID:
		/* got a compatible device ID */
		pnp_addident(pi, pnp_eisaformat(p + i));
		break;
		
	    case END_TAG:
		return;
	    }
	} else {
	    /* large resource */
	    rlen = *(uint16_t *)(p + i);
	    i += sizeof(uint16_t);
	    
	    switch(PNP_LRES_NUM(tag)) {

	    case ID_STRING_ANSI:
		str = malloc(rlen + 1);
		bcopy(p + i, str, rlen);
		str[rlen] = 0;
		if (pi->pi_desc == NULL) {
		    pi->pi_desc = str;
		} else {
		    free(str);
		}
		break;
	    }
	}
    }
}