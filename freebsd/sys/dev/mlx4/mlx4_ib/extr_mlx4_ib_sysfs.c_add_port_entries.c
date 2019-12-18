#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_iov_sysfs_attr_ar {int dummy; } ;
struct mlx4_ib_iov_port {int num; TYPE_1__* dentr_ar; void* cur_port; void* admin_alias_parent; void* gids_parent; void* pkeys_parent; void* mcgs_parent; struct mlx4_ib_dev* dev; } ;
struct mlx4_ib_dev {void* ports_parent; struct mlx4_ib_iov_port* iov_ports; int /*<<< orphan*/  ib_dev; } ;
struct ib_port_attr {int gid_tbl_len; int pkey_tbl_len; } ;
struct TYPE_5__ {int entry_num; } ;
struct TYPE_4__ {TYPE_3__* dentries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __mlx4_ib_query_port (int /*<<< orphan*/ *,int,struct ib_port_attr*,int) ; 
 int create_sysfs_entry (struct mlx4_ib_iov_port*,TYPE_3__*,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 void* kobject_create_and_add (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_get (void*) ; 
 int /*<<< orphan*/  kobject_put (void*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  show_admin_alias_guid ; 
 int /*<<< orphan*/  show_phys_port_pkey ; 
 int /*<<< orphan*/  show_port_gid ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/ * store_admin_alias_guid ; 

__attribute__((used)) static int add_port_entries(struct mlx4_ib_dev *device, int port_num)
{
	int i;
	char buff[10];
	struct mlx4_ib_iov_port *port = NULL;
	int ret = 0 ;
	struct ib_port_attr attr;

	/* get the physical gid and pkey table sizes.*/
	ret = __mlx4_ib_query_port(&device->ib_dev, port_num, &attr, 1);
	if (ret)
		goto err;

	port = &device->iov_ports[port_num - 1];
	port->dev = device;
	port->num = port_num;
	/* Directory structure:
	 * iov -
	 *   port num -
	 *	admin_guids
	 *	gids (operational)
	 *	mcg_table
	 */
	port->dentr_ar = kzalloc(sizeof (struct mlx4_ib_iov_sysfs_attr_ar),
				 GFP_KERNEL);
	if (!port->dentr_ar) {
		ret = -ENOMEM;
		goto err;
	}
	sprintf(buff, "%d", port_num);
	port->cur_port = kobject_create_and_add(buff,
				 kobject_get(device->ports_parent));
	if (!port->cur_port) {
		ret = -ENOMEM;
		goto kobj_create_err;
	}
	/* admin GUIDs */
	port->admin_alias_parent = kobject_create_and_add("admin_guids",
						  kobject_get(port->cur_port));
	if (!port->admin_alias_parent) {
		ret = -ENOMEM;
		goto err_admin_guids;
	}
	for (i = 0 ; i < attr.gid_tbl_len; i++) {
		sprintf(buff, "%d", i);
		port->dentr_ar->dentries[i].entry_num = i;
		ret = create_sysfs_entry(port, &port->dentr_ar->dentries[i],
					  buff, port->admin_alias_parent,
					  show_admin_alias_guid, store_admin_alias_guid);
		if (ret)
			goto err_admin_alias_parent;
	}

	/* gids subdirectory (operational gids) */
	port->gids_parent = kobject_create_and_add("gids",
						  kobject_get(port->cur_port));
	if (!port->gids_parent) {
		ret = -ENOMEM;
		goto err_gids;
	}

	for (i = 0 ; i < attr.gid_tbl_len; i++) {
		sprintf(buff, "%d", i);
		port->dentr_ar->dentries[attr.gid_tbl_len + i].entry_num = i;
		ret = create_sysfs_entry(port,
					 &port->dentr_ar->dentries[attr.gid_tbl_len + i],
					 buff,
					 port->gids_parent, show_port_gid, NULL);
		if (ret)
			goto err_gids_parent;
	}

	/* physical port pkey table */
	port->pkeys_parent =
		kobject_create_and_add("pkeys", kobject_get(port->cur_port));
	if (!port->pkeys_parent) {
		ret = -ENOMEM;
		goto err_pkeys;
	}

	for (i = 0 ; i < attr.pkey_tbl_len; i++) {
		sprintf(buff, "%d", i);
		port->dentr_ar->dentries[2 * attr.gid_tbl_len + i].entry_num = i;
		ret = create_sysfs_entry(port,
					 &port->dentr_ar->dentries[2 * attr.gid_tbl_len + i],
					 buff, port->pkeys_parent,
					 show_phys_port_pkey, NULL);
		if (ret)
			goto err_pkeys_parent;
	}

	/* MCGs table */
	port->mcgs_parent =
		kobject_create_and_add("mcgs", kobject_get(port->cur_port));
	if (!port->mcgs_parent) {
		ret = -ENOMEM;
		goto err_mcgs;
	}
	return 0;

err_mcgs:
	kobject_put(port->cur_port);

err_pkeys_parent:
	kobject_put(port->pkeys_parent);

err_pkeys:
	kobject_put(port->cur_port);

err_gids_parent:
	kobject_put(port->gids_parent);

err_gids:
	kobject_put(port->cur_port);

err_admin_alias_parent:
	kobject_put(port->admin_alias_parent);

err_admin_guids:
	kobject_put(port->cur_port);
	kobject_put(port->cur_port); /* once more for create_and_add buff */

kobj_create_err:
	kobject_put(device->ports_parent);
	kfree(port->dentr_ar);

err:
	pr_err("add_port_entries FAILED: for port:%d, error: %d\n",
	       port_num, ret);
	return ret;
}