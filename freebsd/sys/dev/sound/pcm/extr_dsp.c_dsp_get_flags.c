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
typedef  int uint32_t ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMUNIT (struct cdev*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_devclass ; 
 int pcm_getflags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
dsp_get_flags(struct cdev *dev)
{
	device_t bdev;

	bdev = devclass_get_device(pcm_devclass, PCMUNIT(dev));

	return ((bdev != NULL) ? pcm_getflags(bdev) : 0xffffffff);
}