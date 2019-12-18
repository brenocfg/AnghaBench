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
 scalar_t__ PSMD_RES_LOW ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_mouse_resolution (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ set_mouse_scaling (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_mouse_buttons(KBDC kbdc)
{
	int c = 2;		/* assume two buttons by default */
	int status[3];

	/*
	 * NOTE: a special sequence to obtain Logitech Mouse specific
	 * information: set resolution to 25 ppi, set scaling to 1:1, set
	 * scaling to 1:1, set scaling to 1:1. Then the second byte of the
	 * mouse status bytes is the number of available buttons.
	 * Some manufactures also support this sequence.
	 */
	if (set_mouse_resolution(kbdc, PSMD_RES_LOW) != PSMD_RES_LOW)
		return (c);
	if (set_mouse_scaling(kbdc, 1) && set_mouse_scaling(kbdc, 1) &&
	    set_mouse_scaling(kbdc, 1) &&
	    get_mouse_status(kbdc, status, 0, 3) >= 3 && status[1] != 0)
		return (status[1]);
	return (c);
}