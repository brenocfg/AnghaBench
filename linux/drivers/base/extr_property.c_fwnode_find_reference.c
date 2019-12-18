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
struct fwnode_reference_args {struct fwnode_handle* fwnode; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 struct fwnode_handle* ERR_PTR (int) ; 
 int fwnode_property_get_reference_args (struct fwnode_handle const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,struct fwnode_reference_args*) ; 

struct fwnode_handle *fwnode_find_reference(const struct fwnode_handle *fwnode,
					    const char *name,
					    unsigned int index)
{
	struct fwnode_reference_args args;
	int ret;

	ret = fwnode_property_get_reference_args(fwnode, name, NULL, 0, index,
						 &args);
	return ret ? ERR_PTR(ret) : args.fwnode;
}