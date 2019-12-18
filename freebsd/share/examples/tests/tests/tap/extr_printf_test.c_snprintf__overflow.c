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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fail (char*,...) ; 
 int /*<<< orphan*/  pass () ; 
 int /*<<< orphan*/  skip (int) ; 
 int snprintf (char*,int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
snprintf__overflow(void)
{
	char buffer[10];

	if (snprintf(buffer, sizeof(buffer), "0123456789abcdef") != 16) {
		fail("snprintf did not return the expected "
		    "number of characters");
		skip(1);
		return;
	}
	pass();

	if (strcmp(buffer, "012345678") != 0)
		fail("Bad formatting: got %s", buffer);
	else
		pass();
}