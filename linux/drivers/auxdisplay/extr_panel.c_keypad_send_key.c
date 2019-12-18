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

/* Variables and functions */
 size_t KEYPAD_BUFFER ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keypad_available ; 
 int /*<<< orphan*/ * keypad_buffer ; 
 size_t keypad_buflen ; 
 int /*<<< orphan*/  keypad_read_wait ; 
 int /*<<< orphan*/  keypad_start ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keypad_send_key(const char *string, int max_len)
{
	/* send the key to the device only if a process is attached to it. */
	if (!atomic_read(&keypad_available)) {
		while (max_len-- && keypad_buflen < KEYPAD_BUFFER && *string) {
			keypad_buffer[(keypad_start + keypad_buflen++) %
				      KEYPAD_BUFFER] = *string++;
		}
		wake_up_interruptible(&keypad_read_wait);
	}
}