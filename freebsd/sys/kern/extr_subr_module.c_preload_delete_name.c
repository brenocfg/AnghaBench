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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ MODINFO_ADDR ; 
 scalar_t__ MODINFO_EMPTY ; 
 scalar_t__ MODINFO_NAME ; 
 scalar_t__ MODINFO_SIZE ; 
 int /*<<< orphan*/  kmem_bootstrap_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * preload_metadata ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

void
preload_delete_name(const char *name)
{
    caddr_t	addr, curp;
    uint32_t	*hdr, sz;
    int		next;
    int		clearing;

    addr = 0;
    sz = 0;
    
    if (preload_metadata != NULL) {

	clearing = 0;
	curp = preload_metadata;
	for (;;) {
	    hdr = (uint32_t *)curp;
	    if (hdr[0] == MODINFO_NAME || (hdr[0] == 0 && hdr[1] == 0)) {
		/* Free memory used to store the file. */
		if (addr != 0 && sz != 0)
		    kmem_bootstrap_free((vm_offset_t)addr, sz);
		addr = 0;
		sz = 0;

		if (hdr[0] == 0)
		    break;
		if (!strcmp(name, curp + sizeof(uint32_t) * 2))
		    clearing = 1;	/* got it, start clearing */
		else if (clearing) {
		    clearing = 0;	/* at next one now.. better stop */
		}
	    }
	    if (clearing) {
		if (hdr[0] == MODINFO_ADDR)
		    addr = *(caddr_t *)(curp + sizeof(uint32_t) * 2);
		else if (hdr[0] == MODINFO_SIZE)
		    sz = *(uint32_t *)(curp + sizeof(uint32_t) * 2);
		hdr[0] = MODINFO_EMPTY;
	    }

	    /* skip to next field */
	    next = sizeof(uint32_t) * 2 + hdr[1];
	    next = roundup(next, sizeof(u_long));
	    curp += next;
	}
    }
}