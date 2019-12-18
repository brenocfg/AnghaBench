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
struct hdaa_widget {int dummy; } ;
struct hdaa_devinfo {scalar_t__ startnode; scalar_t__ endnode; struct hdaa_widget* widget; } ;
typedef  scalar_t__ nid_t ;

/* Variables and functions */

struct hdaa_widget *
hdaa_widget_get(struct hdaa_devinfo *devinfo, nid_t nid)
{
	if (devinfo == NULL || devinfo->widget == NULL ||
		    nid < devinfo->startnode || nid >= devinfo->endnode)
		return (NULL);
	return (&devinfo->widget[nid - devinfo->startnode]);
}