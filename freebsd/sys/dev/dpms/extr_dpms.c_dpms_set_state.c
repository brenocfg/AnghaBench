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
 int /*<<< orphan*/  VBE_DPMS_SET_STATE ; 
 int dpms_call_bios (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
dpms_set_state(int state)
{

	return (dpms_call_bios(VBE_DPMS_SET_STATE, &state));
}