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
 int /*<<< orphan*/  VBE_DPMS_GET_SUPPORTED_STATES ; 
 int dpms_call_bios (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
dpms_get_supported_states(int *states)
{

	*states = 0;
	return (dpms_call_bios(VBE_DPMS_GET_SUPPORTED_STATES, states));
}