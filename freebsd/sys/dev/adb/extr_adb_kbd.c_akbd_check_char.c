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
 int FALSE ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (int /*<<< orphan*/ *) ; 
 int akbd_check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
akbd_check_char(keyboard_t *kbd) 
{
	if (!KBD_IS_ACTIVE(kbd))
		return (FALSE);

	return (akbd_check(kbd));
}