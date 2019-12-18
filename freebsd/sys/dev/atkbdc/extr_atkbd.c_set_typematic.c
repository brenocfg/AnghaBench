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
struct TYPE_4__ {int /*<<< orphan*/  kb_delay2; int /*<<< orphan*/  kb_delay1; TYPE_2__* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_5__ {int /*<<< orphan*/  kbdc; } ;
typedef  TYPE_2__ atkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DELAY ; 
 int /*<<< orphan*/  DEFAULT_RATE ; 
 int /*<<< orphan*/  KBDC_SET_TYPEMATIC ; 
 int typematic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typematic_delay (int) ; 
 int /*<<< orphan*/  typematic_rate (int) ; 
 int write_kbd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
set_typematic(keyboard_t *kbd)
{
	int val, error;
	atkbd_state_t *state = kbd->kb_data;

	val = typematic(DEFAULT_DELAY, DEFAULT_RATE);
	error = write_kbd(state->kbdc, KBDC_SET_TYPEMATIC, val);
	if (error == 0) {
		kbd->kb_delay1 = typematic_delay(val);
		kbd->kb_delay2 = typematic_rate(val);
	}

	return (error);
}