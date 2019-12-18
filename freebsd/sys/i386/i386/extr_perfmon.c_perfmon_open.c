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
 int EBUSY ; 
 int ENXIO ; 
 int FWRITE ; 
 int /*<<< orphan*/  perfmon_cpuok ; 
 int writer ; 
 scalar_t__ writerpmc ; 

__attribute__((used)) static int
perfmon_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	if (!perfmon_cpuok)
		return ENXIO;

	if (flags & FWRITE) {
		if (writer) {
			return EBUSY;
		} else {
			writer = 1;
			writerpmc = 0;
		}
	}
	return 0;
}