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
struct apm_bios_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __apm_bios_call ; 
 int on_cpu0 (int /*<<< orphan*/ ,struct apm_bios_call*) ; 

__attribute__((used)) static int apm_bios_call(struct apm_bios_call *call)
{
	return on_cpu0(__apm_bios_call, call);
}