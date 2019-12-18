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
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

void
get_string(char *ptr, int size)
{
	printf("\nEnter string>");

	if (fgets(ptr, size, stdin) == NULL)
		err(1, "Cannot read input");

	ptr[size - 1] = 0;

	size = strlen(ptr);

	/* strip trailing newline, if any */
	if (size == 0)
		return;
	else if (ptr[size - 1] == '\n')
		ptr[size - 1] = 0;
}