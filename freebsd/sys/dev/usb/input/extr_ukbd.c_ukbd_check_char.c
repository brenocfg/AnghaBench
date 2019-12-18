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
 int /*<<< orphan*/  UKBD_LOCK () ; 
 int /*<<< orphan*/  UKBD_UNLOCK () ; 
 int ukbd_check_char_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ukbd_check_char(keyboard_t *kbd)
{
	int result;

	UKBD_LOCK();
	result = ukbd_check_char_locked(kbd);
	UKBD_UNLOCK();

	return (result);
}