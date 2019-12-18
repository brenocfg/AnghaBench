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
typedef  scalar_t__ u_int32_t ;
typedef  char u_char ;

/* Variables and functions */
 scalar_t__ BIOS_PADDRTOVADDR (scalar_t__) ; 
 scalar_t__ BIOS_SIZE ; 
 scalar_t__ BIOS_START ; 
 scalar_t__ BIOS_VADDRTOPADDR (char*) ; 
 int /*<<< orphan*/  bcmp (char*,char*,int) ; 

u_int32_t
bios_sigsearch(u_int32_t start, u_char *sig, int siglen, int paralen, int sigofs)
{
    u_char	*sp, *end;
    
    /* compute the starting address */
    if ((start >= BIOS_START) && (start <= (BIOS_START + BIOS_SIZE))) {
	sp = (char *)BIOS_PADDRTOVADDR(start);
    } else if (start == 0) {
	sp = (char *)BIOS_PADDRTOVADDR(BIOS_START);
    } else {
	return 0;				/* bogus start address */
    }

    /* compute the end address */
    end = (u_char *)BIOS_PADDRTOVADDR(BIOS_START + BIOS_SIZE);

    /* loop searching */
    while ((sp + sigofs + siglen) < end) {
	
	/* compare here */
	if (!bcmp(sp + sigofs, sig, siglen)) {
	    /* convert back to physical address */
	    return((u_int32_t)(uintptr_t)BIOS_VADDRTOPADDR(sp));
	}
	sp += paralen;
    }
    return(0);
}