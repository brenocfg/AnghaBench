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
typedef  int /*<<< orphan*/  u64 ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int fwnode_property_read_int_array (struct fwnode_handle const*,char const*,int,int /*<<< orphan*/ *,size_t) ; 

int fwnode_property_read_u64_array(const struct fwnode_handle *fwnode,
				   const char *propname, u64 *val, size_t nval)
{
	return fwnode_property_read_int_array(fwnode, propname, sizeof(u64),
					      val, nval);
}