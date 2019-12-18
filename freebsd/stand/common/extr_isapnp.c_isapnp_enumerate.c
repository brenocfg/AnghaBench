#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * arch_isaoutb; int /*<<< orphan*/ * arch_isainb; } ;

/* Variables and functions */
 TYPE_1__ archsw ; 
 scalar_t__ isapnp_isolation_protocol () ; 
 int isapnp_readport ; 

__attribute__((used)) static void
isapnp_enumerate(void) 
{
    int		pnp_rd_port;
    
    /* Check for I/O port access */
    if ((archsw.arch_isainb == NULL) || (archsw.arch_isaoutb == NULL))
	return;

    /* 
     * Validate a possibly-suggested read port value.  If the autoscan failed
     * last time, this will return us to autoscan mode again.
     */
    if ((isapnp_readport > 0) &&
	(((isapnp_readport < 0x203) ||
	  (isapnp_readport > 0x3ff) ||
	  (isapnp_readport & 0x3) != 0x3)))
	 /* invalid, go look for ourselves */
	isapnp_readport = 0;

    if (isapnp_readport < 0) {
	/* someone is telling us there is no ISA in the system */
	return;

    } else if (isapnp_readport > 0) {
	/* Someone has told us where the port is/should be, or we found one last time */
	isapnp_isolation_protocol();

    } else {
	/* No clues, look for it ourselves */
	for (pnp_rd_port = 0x80; pnp_rd_port < 0xff; pnp_rd_port += 0x10) {
	    /* Look for something, quit when we find it */
	    isapnp_readport = (pnp_rd_port << 2) | 0x3;
	    if (isapnp_isolation_protocol() > 0)
		break;
	}
    }
}