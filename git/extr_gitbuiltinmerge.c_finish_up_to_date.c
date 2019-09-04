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
 char* _ (char*) ; 
 int /*<<< orphan*/  drop_save () ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 scalar_t__ squash ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void finish_up_to_date(const char *msg)
{
	if (verbosity >= 0)
		printf("%s%s\n", squash ? _(" (nothing to squash)") : "", msg);
	drop_save();
}