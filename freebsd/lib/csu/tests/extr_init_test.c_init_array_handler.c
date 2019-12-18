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
 int init_array_run ; 
 int /*<<< orphan*/  init_array_state ; 
 int /*<<< orphan*/  preinit_array_run ; 

__attribute__((used)) static void
init_array_handler(void)
{

	init_array_run = 1;
	init_array_state = preinit_array_run;
}