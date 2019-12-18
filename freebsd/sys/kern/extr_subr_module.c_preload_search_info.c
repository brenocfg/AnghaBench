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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int roundup (int,int) ; 

caddr_t
preload_search_info(caddr_t mod, int inf)
{
    caddr_t	curp;
    uint32_t	*hdr;
    uint32_t	type = 0;
    int		next;

    if (mod == NULL)
    	return (NULL);

    curp = mod;
    for (;;) {
	hdr = (uint32_t *)curp;
	/* end of module data? */
	if (hdr[0] == 0 && hdr[1] == 0)
	    break;
	/* 
	 * We give up once we've looped back to what we were looking at 
	 * first - this should normally be a MODINFO_NAME field.
	 */
	if (type == 0) {
	    type = hdr[0];
	} else {
	    if (hdr[0] == type)
		break;
	}
	
	/* 
	 * Attribute match? Return pointer to data.
	 * Consumer may safely assume that size value precedes	
	 * data.
	 */
	if (hdr[0] == inf)
	    return(curp + (sizeof(uint32_t) * 2));

	/* skip to next field */
	next = sizeof(uint32_t) * 2 + hdr[1];
	next = roundup(next, sizeof(u_long));
	curp += next;
    }
    return(NULL);
}