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
struct consdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int SC_KERNEL_CONSOLE ; 
 int /*<<< orphan*/  sc_console ; 
 int sc_console_unit ; 
 struct consdev* sc_consptr ; 
 int /*<<< orphan*/  sc_get_cons_priority (int*,int*) ; 
 TYPE_1__* sc_get_softc (int,int) ; 
 int /*<<< orphan*/  sc_get_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scinit (int,int) ; 

__attribute__((used)) static void
sc_cninit(struct consdev *cp)
{
    int unit;
    int flags;

    sc_get_cons_priority(&unit, &flags);
    scinit(unit, flags | SC_KERNEL_CONSOLE);
    sc_console_unit = unit;
    sc_console = sc_get_stat(sc_get_softc(unit, SC_KERNEL_CONSOLE)->dev[0]);
    sc_consptr = cp;
}