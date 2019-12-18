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
 int /*<<< orphan*/  dtmalloc_cdev ; 
 int /*<<< orphan*/  dtmalloc_id ; 
 int /*<<< orphan*/ * dtrace_malloc_probe ; 
 int dtrace_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtmalloc_unload()
{
	int error = 0;

	dtrace_malloc_probe = NULL;

	if ((error = dtrace_unregister(dtmalloc_id)) != 0)
		return (error);

	destroy_dev(dtmalloc_cdev);

	return (error);
}