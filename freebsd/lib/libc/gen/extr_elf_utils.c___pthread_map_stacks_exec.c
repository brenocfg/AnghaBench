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
 size_t INTERPOS_map_stacks_exec ; 
 scalar_t__* __libc_interposing ; 
 void stub1 () ; 

void
__pthread_map_stacks_exec(void)
{

	((void (*)(void))__libc_interposing[INTERPOS_map_stacks_exec])();
}