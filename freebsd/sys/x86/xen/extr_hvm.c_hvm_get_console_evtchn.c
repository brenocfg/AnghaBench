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
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  HVM_PARAM_CONSOLE_EVTCHN ; 
 int /*<<< orphan*/  hvm_get_parameter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static evtchn_port_t
hvm_get_console_evtchn(void)
{

	return (hvm_get_parameter(HVM_PARAM_CONSOLE_EVTCHN));
}