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
typedef  int /*<<< orphan*/  u_int32_t ;
struct vendor_attribute {void* attrib_data; int attrib_len; int attrib_type; int /*<<< orphan*/  vendor_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

int
rad_get_vendor_attr(u_int32_t *vendor, const void **data, size_t *len)
{
	struct vendor_attribute *attr;

	attr = (struct vendor_attribute *)*data;
	*vendor = ntohl(attr->vendor_value);
	*data = attr->attrib_data;
	*len = attr->attrib_len - 2;

	return (attr->attrib_type);
}