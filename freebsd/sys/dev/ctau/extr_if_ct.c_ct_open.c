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
typedef  int /*<<< orphan*/  drv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG2 (int /*<<< orphan*/ *,char*) ; 
 int ENXIO ; 
 size_t NCHAN ; 
 size_t NCTAU ; 
 int /*<<< orphan*/ ** channel ; 
 size_t dev2unit (struct cdev*) ; 

__attribute__((used)) static int ct_open (struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	drv_t *d;

	if (dev2unit(dev) >= NCTAU*NCHAN || ! (d = channel[dev2unit(dev)]))
		return ENXIO;
		
	CT_DEBUG2 (d, ("ct_open\n"));
	return 0;
}