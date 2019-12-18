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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  KMI_LOCK () ; 
 int /*<<< orphan*/  KMI_UNLOCK () ; 
 int /*<<< orphan*/  kmi_read_char_locked (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
kmi_read_char(keyboard_t *kbd, int wait)
{
	uint32_t keycode;

	KMI_LOCK();
	keycode = kmi_read_char_locked(kbd, wait);
	KMI_UNLOCK();

	return (keycode);
}