#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hdaa_pcm_devinfo {int index; int playas; int recas; int digital; struct hdaa_devinfo* devinfo; } ;
struct hdaa_devinfo {int ascnt; int num_devs; struct hdaa_pcm_devinfo* devs; TYPE_1__* chans; int /*<<< orphan*/  dev; struct hdaa_audio_as* as; } ;
struct hdaa_audio_as {scalar_t__ enable; scalar_t__ dir; int digital; int num_chans; size_t* chans; struct hdaa_pcm_devinfo* pdevinfo; } ;
struct TYPE_2__ {struct hdaa_pcm_devinfo* pdevinfo; } ;

/* Variables and functions */
 scalar_t__ HDAA_CTL_IN ; 
 int /*<<< orphan*/  M_HDAA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 

__attribute__((used)) static void
hdaa_prepare_pcms(struct hdaa_devinfo *devinfo)
{
	struct hdaa_audio_as *as = devinfo->as;
	int i, j, k, apdev = 0, ardev = 0, dpdev = 0, drdev = 0;

	for (i = 0; i < devinfo->ascnt; i++) {
		if (as[i].enable == 0)
			continue;
		if (as[i].dir == HDAA_CTL_IN) {
			if (as[i].digital)
				drdev++;
			else
				ardev++;
		} else {
			if (as[i].digital)
				dpdev++;
			else
				apdev++;
		}
	}
	devinfo->num_devs =
	    max(ardev, apdev) + max(drdev, dpdev);
	devinfo->devs =
	    (struct hdaa_pcm_devinfo *)malloc(
	    devinfo->num_devs * sizeof(struct hdaa_pcm_devinfo),
	    M_HDAA, M_ZERO | M_NOWAIT);
	if (devinfo->devs == NULL) {
		device_printf(devinfo->dev,
		    "Unable to allocate memory for devices\n");
		return;
	}
	for (i = 0; i < devinfo->num_devs; i++) {
		devinfo->devs[i].index = i;
		devinfo->devs[i].devinfo = devinfo;
		devinfo->devs[i].playas = -1;
		devinfo->devs[i].recas = -1;
		devinfo->devs[i].digital = 255;
	}
	for (i = 0; i < devinfo->ascnt; i++) {
		if (as[i].enable == 0)
			continue;
		for (j = 0; j < devinfo->num_devs; j++) {
			if (devinfo->devs[j].digital != 255 &&
			    (!devinfo->devs[j].digital) !=
			    (!as[i].digital))
				continue;
			if (as[i].dir == HDAA_CTL_IN) {
				if (devinfo->devs[j].recas >= 0)
					continue;
				devinfo->devs[j].recas = i;
			} else {
				if (devinfo->devs[j].playas >= 0)
					continue;
				devinfo->devs[j].playas = i;
			}
			as[i].pdevinfo = &devinfo->devs[j];
			for (k = 0; k < as[i].num_chans; k++) {
				devinfo->chans[as[i].chans[k]].pdevinfo =
				    &devinfo->devs[j];
			}
			devinfo->devs[j].digital = as[i].digital;
			break;
		}
	}
}