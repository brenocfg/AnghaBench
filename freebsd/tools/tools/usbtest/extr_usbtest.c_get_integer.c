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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
get_integer(void)
{
	char buf[32];

	printf("\nEnter integer value>");

	if (fgets(buf, sizeof(buf), stdin) == NULL)
		err(1, "Cannot read input");

	if (strcmp(buf, "x\n") == 0)
		return (-1);
	if (strcmp(buf, "r\n") == 0)
		return (-2);

	return ((int)strtol(buf, 0, 0));
}