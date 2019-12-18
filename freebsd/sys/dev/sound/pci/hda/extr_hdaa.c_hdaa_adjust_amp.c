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
struct hdaa_widget {size_t bindas; struct hdaa_devinfo* devinfo; } ;
struct hdaa_pcm_devinfo {int ossmask; int* minamp; int* maxamp; } ;
struct hdaa_devinfo {struct hdaa_pcm_devinfo* devs; TYPE_1__* as; } ;
struct TYPE_2__ {struct hdaa_pcm_devinfo* pdevinfo; } ;

/* Variables and functions */
 int imax (int,int) ; 
 int imin (int,int) ; 

__attribute__((used)) static void
hdaa_adjust_amp(struct hdaa_widget *w, int ossdev,
    int found, int minamp, int maxamp)
{
	struct hdaa_devinfo *devinfo = w->devinfo;
	struct hdaa_pcm_devinfo *pdevinfo;

	if (w->bindas >= 0)
		pdevinfo = devinfo->as[w->bindas].pdevinfo;
	else
		pdevinfo = &devinfo->devs[0];
	if (found)
		pdevinfo->ossmask |= (1 << ossdev);
	if (minamp == 0 && maxamp == 0)
		return;
	if (pdevinfo->minamp[ossdev] == 0 && pdevinfo->maxamp[ossdev] == 0) {
		pdevinfo->minamp[ossdev] = minamp;
		pdevinfo->maxamp[ossdev] = maxamp;
	} else {
		pdevinfo->minamp[ossdev] = imax(pdevinfo->minamp[ossdev], minamp);
		pdevinfo->maxamp[ossdev] = imin(pdevinfo->maxamp[ossdev], maxamp);
	}
}