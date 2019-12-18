#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ out_port; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ osm_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_spinlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_spinlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int open_out_port (TYPE_1__*) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 

int osm_log_reopen_file(osm_log_t * p_log)
{
	int ret;

	if (p_log->out_port == stdout || p_log->out_port == stderr)
		return 0;
	cl_spinlock_acquire(&p_log->lock);
	fclose(p_log->out_port);
	ret = open_out_port(p_log);
	cl_spinlock_release(&p_log->lock);
	return ret;
}