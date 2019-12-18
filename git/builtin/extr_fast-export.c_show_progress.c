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
 int /*<<< orphan*/  printf (char*,int) ; 
 int progress ; 

__attribute__((used)) static void show_progress(void)
{
	static int counter = 0;
	if (!progress)
		return;
	if ((++counter % progress) == 0)
		printf("progress %d objects\n", counter);
}