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
 int dm_test_targets () ; 
 int dm_test_versions () ; 
 int /*<<< orphan*/  err (int,char*) ; 

int
main(int argc, char **argv) {
	int error;

	error = 0;

	error = dm_test_versions();
	if (error != 0)
		err(1, "dm_test_versions failed");

	error = dm_test_targets();
	if (error != 0)
		err(1, "dm_test_targets failed");

	return error;
}