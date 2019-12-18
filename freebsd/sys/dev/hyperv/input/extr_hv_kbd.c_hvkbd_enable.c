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
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  HVKBD_LOCK () ; 
 int /*<<< orphan*/  HVKBD_UNLOCK () ; 
 int /*<<< orphan*/  KBD_ACTIVATE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hvkbd_enable(keyboard_t *kbd)
{
	HVKBD_LOCK();
	KBD_ACTIVATE(kbd);
	HVKBD_UNLOCK();
	return (0);
}