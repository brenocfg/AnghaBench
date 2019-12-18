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
 int osm_exit_flag ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void mark_exit_flag(int signum)
{
	if (!osm_exit_flag)
		printf("OpenSM: Got signal %d - exiting...\n", signum);
	osm_exit_flag = 1;
}