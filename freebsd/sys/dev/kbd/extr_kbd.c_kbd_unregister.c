#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* kc_func ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  kc_arg; } ;
struct TYPE_9__ {size_t kb_index; TYPE_1__ kb_callback; } ;
typedef  TYPE_2__ keyboard_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  KBDIO_UNLOADING ; 
 int /*<<< orphan*/  KBD_INVALID (TYPE_2__*) ; 
 scalar_t__ KBD_IS_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/ ** kbdsw ; 
 TYPE_2__** keyboard ; 
 size_t keyboards ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
kbd_unregister(keyboard_t *kbd)
{
	int error;
	int s;

	if ((kbd->kb_index < 0) || (kbd->kb_index >= keyboards))
		return (ENOENT);
	if (keyboard[kbd->kb_index] != kbd)
		return (ENOENT);

	s = spltty();
	if (KBD_IS_BUSY(kbd)) {
		error = (*kbd->kb_callback.kc_func)(kbd, KBDIO_UNLOADING,
		    kbd->kb_callback.kc_arg);
		if (error) {
			splx(s);
			return (error);
		}
		if (KBD_IS_BUSY(kbd)) {
			splx(s);
			return (EBUSY);
		}
	}
	KBD_INVALID(kbd);
	keyboard[kbd->kb_index] = NULL;
	kbdsw[kbd->kb_index] = NULL;

	splx(s);
	return (0);
}