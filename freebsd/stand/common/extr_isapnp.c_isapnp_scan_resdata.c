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
typedef  int u_int ;
typedef  size_t u_char ;
struct pnpinfo {char* pi_desc; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  COMP_DEVICE_ID 130 
#define  END_TAG 129 
#define  ID_STRING_ANSI 128 
 int PNP_LRES_NUM (size_t) ; 
 scalar_t__ PNP_RES_TYPE (size_t) ; 
 int PNP_SRES_LEN (size_t) ; 
 int PNP_SRES_NUM (size_t) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 scalar_t__ isapnp_get_resource_info (size_t*,int) ; 
 size_t* malloc (size_t) ; 
 int /*<<< orphan*/  pnp_addident (struct pnpinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_eisaformat (size_t*) ; 

__attribute__((used)) static int
isapnp_scan_resdata(struct pnpinfo *pi)
{
    u_char	tag, resinfo[8];
    u_int	limit;
    size_t	large_len;
    u_char	*str;

    limit = 1000;
    while ((limit-- > 0) && !isapnp_get_resource_info(&tag, 1)) {
	if (PNP_RES_TYPE(tag) == 0) {
	    /* Small resource */
	    switch (PNP_SRES_NUM(tag)) {

		case COMP_DEVICE_ID:
		    /* Got a compatible device id resource */
		    if (isapnp_get_resource_info(resinfo, PNP_SRES_LEN(tag)))
			return(1);
		    pnp_addident(pi, pnp_eisaformat(resinfo));

		case END_TAG:
		    return(0);
		    break;

		default:
		    /* Skip this resource */
		    if (isapnp_get_resource_info(NULL, PNP_SRES_LEN(tag)))
			return(1);
		    break;
	    }
	} else {
	    /* Large resource */
	    if (isapnp_get_resource_info(resinfo, 2))
		return(1);

	    large_len = resinfo[1];
	    large_len = (large_len << 8) + resinfo[0];

	    switch(PNP_LRES_NUM(tag)) {

	    case ID_STRING_ANSI:
		str = malloc(large_len + 1);
		if (isapnp_get_resource_info(str, (ssize_t)large_len)) {
		    free(str);
		    return(1);
		}
		str[large_len] = 0;
		if (pi->pi_desc == NULL) {
		    pi->pi_desc = (char *)str;
		} else {
		    free(str);
		}
		break;
		
	    default:
		/* Large resource, skip it */
		if (isapnp_get_resource_info(NULL, (ssize_t)large_len))
		    return(1);
	    }
	}
    }
    return(1);
}