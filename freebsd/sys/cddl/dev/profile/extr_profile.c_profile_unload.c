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
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int dtrace_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_cdev ; 
 int /*<<< orphan*/  profile_id ; 

__attribute__((used)) static int
profile_unload()
{
	int error = 0;

	if ((error = dtrace_unregister(profile_id)) != 0)
		return (error);

	destroy_dev(profile_cdev);

	return (error);
}