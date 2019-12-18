#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent_cfg_hdl; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
union md_node_info {TYPE_1__ vdev_port; } ;
typedef  int /*<<< orphan*/  u64 ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 void* mdesc_get_property (struct mdesc_handle*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parent_cfg_handle (struct mdesc_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_vdev_port_node_info(struct mdesc_handle *md, u64 node,
				   union md_node_info *node_info)
{
	const u64 *parent_cfg_hdlp;
	const char *name;
	const u64 *idp;

	/*
	 * Virtual device nodes are distinguished by:
	 * 1. "id" property
	 * 2. "name" property
	 * 3. parent node "cfg-handle" property
	 */
	idp = mdesc_get_property(md, node, "id", NULL);
	name = mdesc_get_property(md, node, "name", NULL);
	parent_cfg_hdlp = parent_cfg_handle(md, node);

	if (!idp || !name || !parent_cfg_hdlp)
		return -1;

	node_info->vdev_port.id = *idp;
	node_info->vdev_port.name = kstrdup_const(name, GFP_KERNEL);
	if (!node_info->vdev_port.name)
		return -1;
	node_info->vdev_port.parent_cfg_hdl = *parent_cfg_hdlp;

	return 0;
}