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
typedef  int /*<<< orphan*/  ts ;
struct thread {int /*<<< orphan*/  td_retval; } ;
struct cloudabi_sys_clock_time_get_args {int /*<<< orphan*/  clock_id; } ;
typedef  int /*<<< orphan*/  cloudabi_timestamp_t ;

/* Variables and functions */
 int cloudabi_clock_time_get (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
cloudabi_sys_clock_time_get(struct thread *td,
    struct cloudabi_sys_clock_time_get_args *uap)
{
	cloudabi_timestamp_t ts;
	int error;

	error = cloudabi_clock_time_get(td, uap->clock_id, &ts);
	memcpy(td->td_retval, &ts, sizeof(ts));
	return (error);
}