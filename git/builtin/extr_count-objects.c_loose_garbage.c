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
 int /*<<< orphan*/  PACKDIR_FILE_GARBAGE ; 
 int /*<<< orphan*/  report_garbage (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void loose_garbage(const char *path)
{
	if (verbose)
		report_garbage(PACKDIR_FILE_GARBAGE, path);
}