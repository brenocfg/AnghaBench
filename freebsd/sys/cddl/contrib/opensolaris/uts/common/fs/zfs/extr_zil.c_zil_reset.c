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
 int /*<<< orphan*/  EEXIST ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int zil_suspend (char const*,int /*<<< orphan*/ *) ; 

int
zil_reset(const char *osname, void *arg)
{
	int error;

	error = zil_suspend(osname, NULL);
	if (error != 0)
		return (SET_ERROR(EEXIST));
	return (0);
}