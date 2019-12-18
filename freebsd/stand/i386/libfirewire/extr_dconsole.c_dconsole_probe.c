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
struct console {int c_flags; } ;

/* Variables and functions */
 int C_ACTIVEIN ; 
 int C_ACTIVEOUT ; 
 int C_PRESENTIN ; 
 int C_PRESENTOUT ; 
 int /*<<< orphan*/  dconsole_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dconsole_probe(struct console *cp)
{
    /* XXX check the BIOS equipment list? */
    cp->c_flags |= (C_PRESENTIN | C_PRESENTOUT);
#if DCONSOLE_AS_MULTI_CONSOLE
    dconsole_init(0);
    cp->c_flags |= (C_ACTIVEIN | C_ACTIVEOUT);
#endif
}