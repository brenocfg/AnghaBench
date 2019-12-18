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
 int /*<<< orphan*/  plan_a (char const*) ; 
 int /*<<< orphan*/  plan_b (char const*) ; 
 int /*<<< orphan*/  say (char*,char const*,char*) ; 
 scalar_t__ using_plan_a ; 
 scalar_t__ verbose ; 

void
scan_input(const char *filename)
{
	if (!plan_a(filename))
		plan_b(filename);
	if (verbose) {
		say("Patching file %s using Plan %s...\n", filename,
		    (using_plan_a ? "A" : "B"));
	}
}