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
typedef  int /*<<< orphan*/  devcon_match_fn_t ;

/* Variables and functions */
 void* fwnode_devcon_match (struct fwnode_handle*,char const*,void*,int /*<<< orphan*/ ) ; 
 void* fwnode_graph_devcon_match (struct fwnode_handle*,char const*,void*,int /*<<< orphan*/ ) ; 

void *fwnode_connection_find_match(struct fwnode_handle *fwnode,
				   const char *con_id, void *data,
				   devcon_match_fn_t match)
{
	void *ret;

	if (!fwnode || !match)
		return NULL;

	ret = fwnode_graph_devcon_match(fwnode, con_id, data, match);
	if (ret)
		return ret;

	return fwnode_devcon_match(fwnode, con_id, data, match);
}