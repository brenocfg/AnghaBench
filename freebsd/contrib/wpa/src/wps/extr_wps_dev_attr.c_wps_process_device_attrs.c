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
struct wps_parse_attr {int /*<<< orphan*/  dev_name_len; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  primary_dev_type; int /*<<< orphan*/  serial_number_len; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_number_len; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name_len; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer_len; int /*<<< orphan*/  manufacturer; } ;
struct wps_device_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ wps_process_dev_name (struct wps_device_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_manufacturer (struct wps_device_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_model_name (struct wps_device_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_model_number (struct wps_device_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_primary_dev_type (struct wps_device_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_serial_number (struct wps_device_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wps_process_device_attrs(struct wps_device_data *dev,
			     struct wps_parse_attr *attr)
{
	if (wps_process_manufacturer(dev, attr->manufacturer,
				     attr->manufacturer_len) ||
	    wps_process_model_name(dev, attr->model_name,
				   attr->model_name_len) ||
	    wps_process_model_number(dev, attr->model_number,
				     attr->model_number_len) ||
	    wps_process_serial_number(dev, attr->serial_number,
				      attr->serial_number_len) ||
	    wps_process_primary_dev_type(dev, attr->primary_dev_type) ||
	    wps_process_dev_name(dev, attr->dev_name, attr->dev_name_len))
		return -1;
	return 0;
}