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
 int /*<<< orphan*/  internal_initialized ; 
 int mac_init_internal (int) ; 

__attribute__((used)) static int
mac_maybe_init_internal(void)
{

	if (!internal_initialized)
		return (mac_init_internal(1));
	else
		return (0);
}