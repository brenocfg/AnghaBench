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
struct TYPE_4__ {int flags; scalar_t__ poll_count; scalar_t__ poll_state; } ;

/* Variables and functions */
 int SCF_AUTO ; 
 int SCF_CONNECTED ; 
 int /*<<< orphan*/  nglmi_startup (TYPE_1__*) ; 

__attribute__((used)) static void
nglmi_startup_auto(sc_p sc)
{
	sc->flags |= (SCF_AUTO | SCF_CONNECTED);
	sc->poll_state = 0;	/* reset state machine */
	sc->poll_count = 0;
	nglmi_startup(sc);
}