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
struct wps_device_data {int dummy; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ wps_build_dev_name (struct wps_device_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_manufacturer (struct wps_device_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_model_name (struct wps_device_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_model_number (struct wps_device_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_primary_dev_type (struct wps_device_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_serial_number (struct wps_device_data*,struct wpabuf*) ; 

int wps_build_device_attrs(struct wps_device_data *dev, struct wpabuf *msg)
{
	if (wps_build_manufacturer(dev, msg) ||
	    wps_build_model_name(dev, msg) ||
	    wps_build_model_number(dev, msg) ||
	    wps_build_serial_number(dev, msg) ||
	    wps_build_primary_dev_type(dev, msg) ||
	    wps_build_dev_name(dev, msg))
		return -1;
	return 0;
}