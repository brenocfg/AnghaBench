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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
snprintf__two_formatters(void)
{
	char buffer[128];

	if (snprintf(buffer, sizeof(buffer), "%s, %s!", "Hello",
	    "tests") <= 0)
		errx(EXIT_FAILURE, "snprintf with two formatters failed");

	if (strcmp(buffer, "Hello, tests!") != 0)
		errx(EXIT_FAILURE, "Bad formatting: got %s", buffer);
}