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
struct hdaa_pcm_devinfo {scalar_t__ registered; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdaa_pcm_detach(device_t dev)
{
	struct hdaa_pcm_devinfo *pdevinfo =
	    (struct hdaa_pcm_devinfo *)device_get_ivars(dev);
	int err;

	if (pdevinfo->registered > 0) {
		err = pcm_unregister(dev);
		if (err != 0)
			return (err);
	}

	return (0);
}