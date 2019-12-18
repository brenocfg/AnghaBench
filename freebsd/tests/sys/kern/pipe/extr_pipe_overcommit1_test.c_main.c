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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 unsigned int nitems (int*) ; 
 int /*<<< orphan*/  pipe (int*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
main(void)
{
	int pipes[10000];
	unsigned int i;

	for (i = 0; i < nitems(pipes); i++)
		(void)pipe(&pipes[i]);
	printf("PASS\n");

	exit(0);
}