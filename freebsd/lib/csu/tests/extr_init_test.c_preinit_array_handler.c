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
 int /*<<< orphan*/  init_array_run ; 
 int preinit_array_run ; 
 int /*<<< orphan*/  preinit_array_state ; 

__attribute__((used)) static void
preinit_array_handler(void)
{

	preinit_array_run = 1;
	preinit_array_state = init_array_run;
}