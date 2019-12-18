#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; TYPE_1__* sc; } ;
typedef  TYPE_2__ scr_stat ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  kbd; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTL ; 
 int /*<<< orphan*/  KDGKBSTATE ; 
 int LOCK_MASK ; 
 int kbdd_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
save_kbd_state(scr_stat *scp)
{
    int state;
    int error;

    error = kbdd_ioctl(scp->sc->kbd, KDGKBSTATE, (caddr_t)&state);
    if (error == ENOIOCTL)
	error = ENODEV;
    if (error == 0) {
	scp->status &= ~LOCK_MASK;
	scp->status |= state;
    }
    return error;
}