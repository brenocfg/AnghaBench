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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int MODINFO_NAME ; 
 int /*<<< orphan*/ * preload_metadata ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ *) ; 

caddr_t
preload_search_by_name(const char *name)
{
    caddr_t	curp;
    uint32_t	*hdr;
    int		next;
    
    if (preload_metadata != NULL) {
	
	curp = preload_metadata;
	for (;;) {
	    hdr = (uint32_t *)curp;
	    if (hdr[0] == 0 && hdr[1] == 0)
		break;

	    /* Search for a MODINFO_NAME field */
	    if ((hdr[0] == MODINFO_NAME) &&
		!strcmp(name, curp + sizeof(uint32_t) * 2))
		return(curp);

	    /* skip to next field */
	    next = sizeof(uint32_t) * 2 + hdr[1];
	    next = roundup(next, sizeof(u_long));
	    curp += next;
	}
    }
    return(NULL);
}