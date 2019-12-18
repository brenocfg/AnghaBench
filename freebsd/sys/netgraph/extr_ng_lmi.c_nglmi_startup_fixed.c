#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  lmi_channel; } ;

/* Variables and functions */
 int SCF_CONNECTED ; 
 int SCF_FIXED ; 
 int /*<<< orphan*/  nglmi_startup (TYPE_1__*) ; 

__attribute__((used)) static void
nglmi_startup_fixed(sc_p sc, hook_p hook)
{
	sc->flags |= (SCF_FIXED | SCF_CONNECTED);
	sc->lmi_channel = hook;
	nglmi_startup(sc);
}