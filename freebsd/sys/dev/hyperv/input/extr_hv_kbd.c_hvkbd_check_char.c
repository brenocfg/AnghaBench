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
 int hvkbd_check_char_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hvkbd_check_char(keyboard_t *kbd)
{
	int result;

	HVKBD_LOCK();
	result = hvkbd_check_char_locked(kbd);
	HVKBD_UNLOCK();

	return (result);
}