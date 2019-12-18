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
struct TYPE_4__ {int running; int /*<<< orphan*/  chan; } ;
typedef  TYPE_1__ drv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ct_set_dtr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ct_set_rts (int /*<<< orphan*/ ,int) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void ct_up (drv_t *d)
{
	int s = splimp ();
	CT_DEBUG (d, ("ct_up\n"));
	ct_set_dtr (d->chan, 1);
	ct_set_rts (d->chan, 1);
	d->running = 1;
	splx (s);
}