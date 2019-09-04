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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int write_error(const char *filename)
{
	error(_("failed to write new configuration file %s"), filename);

	/* Same error code as "failed to rename". */
	return 4;
}