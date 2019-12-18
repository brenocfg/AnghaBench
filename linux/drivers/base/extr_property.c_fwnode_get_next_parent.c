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
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 struct fwnode_handle* fwnode_get_parent (struct fwnode_handle*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 

struct fwnode_handle *fwnode_get_next_parent(struct fwnode_handle *fwnode)
{
	struct fwnode_handle *parent = fwnode_get_parent(fwnode);

	fwnode_handle_put(fwnode);

	return parent;
}