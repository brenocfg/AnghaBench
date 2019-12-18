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
 struct fwnode_handle* fwnode_get_next_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_graph_get_remote_endpoint (struct fwnode_handle const*) ; 

struct fwnode_handle *
fwnode_graph_get_remote_port(const struct fwnode_handle *fwnode)
{
	return fwnode_get_next_parent(fwnode_graph_get_remote_endpoint(fwnode));
}