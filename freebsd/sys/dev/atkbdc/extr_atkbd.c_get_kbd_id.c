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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  KBDC_SEND_DEV_ID ; 
 scalar_t__ KBD_ACK ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int read_kbd_data (int /*<<< orphan*/ ) ; 
 scalar_t__ send_kbd_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_kbd_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_kbd_id(KBDC kbdc)
{
	int id1, id2;

	empty_both_buffers(kbdc, 10);
	id1 = id2 = -1;
	if (send_kbd_command(kbdc, KBDC_SEND_DEV_ID) != KBD_ACK)
		return -1;

	DELAY(10000); 	/* 10 msec delay */
	id1 = read_kbd_data(kbdc);
	if (id1 != -1)
		id2 = read_kbd_data(kbdc);

	if ((id1 == -1) || (id2 == -1)) {
		empty_both_buffers(kbdc, 10);
		test_controller(kbdc);
		test_kbd_port(kbdc);
		return -1;
	}
	return ((id2 << 8) | id1);
}