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
struct timezone {scalar_t__ tz_dsttime; scalar_t__ tz_minuteswest; int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct thread {int dummy; } ;
struct linux_gettimeofday_args {int /*<<< orphan*/ * tzp; int /*<<< orphan*/ * tp; } ;
typedef  int /*<<< orphan*/  rtz ;
typedef  struct timezone l_timeval ;
typedef  int /*<<< orphan*/  atv32 ;

/* Variables and functions */
 int copyout (struct timezone*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 

int
linux_gettimeofday(struct thread *td, struct linux_gettimeofday_args *uap)
{
	struct timeval atv;
	l_timeval atv32;
	struct timezone rtz;
	int error = 0;

	if (uap->tp) {
		microtime(&atv);
		atv32.tv_sec = atv.tv_sec;
		atv32.tv_usec = atv.tv_usec;
		error = copyout(&atv32, uap->tp, sizeof(atv32));
	}
	if (error == 0 && uap->tzp != NULL) {
		rtz.tz_minuteswest = 0;
		rtz.tz_dsttime = 0;
		error = copyout(&rtz, uap->tzp, sizeof(rtz));
	}
	return (error);
}