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
struct hdaa_devinfo {int /*<<< orphan*/  widget; int /*<<< orphan*/  poll_jack; scalar_t__ poll_ival; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_HDAA ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct hdaa_devinfo* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_lock (struct hdaa_devinfo*) ; 
 int /*<<< orphan*/  hdaa_unconfigure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_unlock (struct hdaa_devinfo*) ; 

__attribute__((used)) static int
hdaa_detach(device_t dev)
{
	struct hdaa_devinfo *devinfo = device_get_softc(dev);
	int error;

	if ((error = device_delete_children(dev)) != 0)
		return (error);

	hdaa_lock(devinfo);
	hdaa_unconfigure(dev);
	devinfo->poll_ival = 0;
	callout_stop(&devinfo->poll_jack);
	hdaa_unlock(devinfo);
	callout_drain(&devinfo->poll_jack);

	free(devinfo->widget, M_HDAA);
	return (0);
}