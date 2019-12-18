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
struct timezone {scalar_t__ tz_dsttime; scalar_t__ tz_minuteswest; } ;
struct timeval {scalar_t__ tz_dsttime; scalar_t__ tz_minuteswest; } ;
struct thread {int dummy; } ;
struct gettimeofday_args {int /*<<< orphan*/ * tzp; int /*<<< orphan*/ * tp; } ;
typedef  int /*<<< orphan*/  rtz ;
typedef  int /*<<< orphan*/  atv ;

/* Variables and functions */
 int copyout (struct timezone*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  microtime (struct timezone*) ; 

int
sys_gettimeofday(struct thread *td, struct gettimeofday_args *uap)
{
	struct timeval atv;
	struct timezone rtz;
	int error = 0;

	if (uap->tp) {
		microtime(&atv);
		error = copyout(&atv, uap->tp, sizeof (atv));
	}
	if (error == 0 && uap->tzp != NULL) {
		rtz.tz_minuteswest = 0;
		rtz.tz_dsttime = 0;
		error = copyout(&rtz, uap->tzp, sizeof (rtz));
	}
	return (error);
}