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
 scalar_t__ decimal ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_integer_arg(const char *(*decoder)(int), int value)
{
	const char *str;

	str = decoder(value);
	if (str != NULL)
		printf("%s", str);
	else {
		if (decimal)
			printf("<invalid=%d>", value);
		else
			printf("<invalid=%#x>", value);
	}
}