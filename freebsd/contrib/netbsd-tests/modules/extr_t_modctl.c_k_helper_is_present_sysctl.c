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
typedef  int /*<<< orphan*/  present ;

/* Variables and functions */
 int get_sysctl (char*,size_t*,int) ; 

__attribute__((used)) static bool
k_helper_is_present_sysctl(void)
{
	size_t present;

	return get_sysctl("vendor.k_helper.present", &present,
	    sizeof(present));
}