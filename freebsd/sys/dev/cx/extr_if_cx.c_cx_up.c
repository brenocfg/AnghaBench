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
 int /*<<< orphan*/  CX_DEBUG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cx_set_dtr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set_rts (int /*<<< orphan*/ ,int) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void cx_up (drv_t *d)
{
	int s = splhigh ();
	CX_DEBUG (d, ("cx_up\n"));
	cx_set_dtr (d->chan, 1);
	cx_set_rts (d->chan, 1);
	d->running = 1;
	splx (s);
}