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
 scalar_t__ netmap_verbose ; 
 int /*<<< orphan*/  nm_prinf (char*,struct cdev*,int,int,struct thread*) ; 

__attribute__((used)) static int
netmap_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	if (netmap_verbose)
		nm_prinf("dev %p fflag 0x%x devtype %d td %p",
			dev, fflag, devtype, td);
	return 0;
}