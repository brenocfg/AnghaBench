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
struct TYPE_4__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_5__ {int /*<<< orphan*/  kbdc; } ;
typedef  TYPE_2__ atkbd_state_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  test_controller (int /*<<< orphan*/ ) ; 
 scalar_t__ test_kbd_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbd_test_if(keyboard_t *kbd)
{
	int error;
	int s;

	error = 0;
	empty_both_buffers(((atkbd_state_t *)kbd->kb_data)->kbdc, 10);
	s = spltty();
	if (!test_controller(((atkbd_state_t *)kbd->kb_data)->kbdc))
		error = EIO;
	else if (test_kbd_port(((atkbd_state_t *)kbd->kb_data)->kbdc) != 0)
		error = EIO;
	splx(s);

	return error;
}