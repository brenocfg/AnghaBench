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
struct timespec {int dummy; } ;
struct thread {int /*<<< orphan*/  td_retval; } ;
struct cloudabi_sys_clock_res_get_args {int /*<<< orphan*/  clock_id; } ;
typedef  int /*<<< orphan*/  cts ;
typedef  int /*<<< orphan*/  cloudabi_timestamp_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int cloudabi_convert_clockid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cloudabi_convert_timespec (struct timespec*,int /*<<< orphan*/ *) ; 
 int kern_clock_getres (struct thread*,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
cloudabi_sys_clock_res_get(struct thread *td,
    struct cloudabi_sys_clock_res_get_args *uap)
{
	struct timespec ts;
	cloudabi_timestamp_t cts;
	int error;
	clockid_t clockid;

	error = cloudabi_convert_clockid(uap->clock_id, &clockid);
	if (error != 0)
		return (error);
	error = kern_clock_getres(td, clockid, &ts);
	if (error != 0)
		return (error);
	error = cloudabi_convert_timespec(&ts, &cts);
	if (error != 0)
		return (error);
	memcpy(td->td_retval, &cts, sizeof(cts));
	return (0);
}