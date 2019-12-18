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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int FWRITE ; 
 int NPMC ; 
 int /*<<< orphan*/  perfmon_fini (int) ; 
 scalar_t__ writer ; 
 int writerpmc ; 

__attribute__((used)) static int
perfmon_close(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	if (flags & FWRITE) {
		int i;

		for (i = 0; i < NPMC; i++) {
			if (writerpmc & (1 << i))
				perfmon_fini(i);
		}
		writer = 0;
	}
	return 0;
}