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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ arc4_count ; 
 int /*<<< orphan*/  arc4_stir () ; 
 scalar_t__ arc4_stir_pid ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  rs_initialized ; 

__attribute__((used)) static void
arc4_stir_if_needed(void)
{
	pid_t pid = getpid();

	if (arc4_count <= 0 || !rs_initialized || arc4_stir_pid != pid)
	{
		arc4_stir_pid = pid;
		arc4_stir();
	}
}