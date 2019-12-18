#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max_startups; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ options ; 
 int* startup_pipes ; 

__attribute__((used)) static void
close_startup_pipes(void)
{
	int i;

	if (startup_pipes)
		for (i = 0; i < options.max_startups; i++)
			if (startup_pipes[i] != -1)
				close(startup_pipes[i]);
}