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
 int /*<<< orphan*/  DTRACE_PRIV_USER ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  dtmalloc_attr ; 
 int /*<<< orphan*/  dtmalloc_cdev ; 
 int /*<<< orphan*/  dtmalloc_cdevsw ; 
 int /*<<< orphan*/  dtmalloc_id ; 
 int /*<<< orphan*/  dtmalloc_pops ; 
 int /*<<< orphan*/  dtrace_malloc_probe ; 
 int /*<<< orphan*/  dtrace_probe ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
dtmalloc_load(void *dummy)
{
	/* Create the /dev/dtrace/dtmalloc entry. */
	dtmalloc_cdev = make_dev(&dtmalloc_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600,
	    "dtrace/dtmalloc");

	if (dtrace_register("dtmalloc", &dtmalloc_attr, DTRACE_PRIV_USER,
	    NULL, &dtmalloc_pops, NULL, &dtmalloc_id) != 0)
		return;

	dtrace_malloc_probe = dtrace_probe;
}