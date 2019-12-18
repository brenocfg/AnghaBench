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
struct hdaa_pcm_devinfo {int /*<<< orphan*/  dev; } ;
struct hdaa_devinfo {int num_devs; int /*<<< orphan*/  dev; struct hdaa_pcm_devinfo* devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
hdaa_create_pcms(struct hdaa_devinfo *devinfo)
{
	int i;

	for (i = 0; i < devinfo->num_devs; i++) {
		struct hdaa_pcm_devinfo *pdevinfo = &devinfo->devs[i];

		pdevinfo->dev = device_add_child(devinfo->dev, "pcm", -1);
		device_set_ivars(pdevinfo->dev, (void *)pdevinfo);
	}
}