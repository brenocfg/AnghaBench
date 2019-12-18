#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * type; int /*<<< orphan*/  release; int /*<<< orphan*/ * driver; } ;
struct TYPE_7__ {char* name; int id; TYPE_1__ dev; } ;
struct ipmi_device_id {int /*<<< orphan*/  device_id; int /*<<< orphan*/  product_id; int /*<<< orphan*/  manufacturer_id; } ;
struct bmc_device {int dyn_id_set; int dyn_guid_set; TYPE_2__ pdev; int /*<<< orphan*/  dyn_mutex; int /*<<< orphan*/  usecount; struct ipmi_device_id id; int /*<<< orphan*/  intfs; scalar_t__ dyn_id_expiry; int /*<<< orphan*/  guid; int /*<<< orphan*/  remove_work; } ;
struct ipmi_smi {int in_bmc_register; int intf_num; char* my_dev_name; int bmc_registered; struct bmc_device tmp_bmc; struct bmc_device* bmc; int /*<<< orphan*/  bmc_link; TYPE_4__* si_dev; int /*<<< orphan*/  bmc_reg_mutex; } ;
typedef  int /*<<< orphan*/  guid_t ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IPMI_DYN_DEV_ID_EXPIRY ; 
 int /*<<< orphan*/  bmc_device_type ; 
 int /*<<< orphan*/  cleanup_bmc_device ; 
 int /*<<< orphan*/  cleanup_bmc_work ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_bmc_ida ; 
 struct bmc_device* ipmi_find_bmc_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bmc_device* ipmi_find_bmc_prod_dev_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ ipmidriver ; 
 int /*<<< orphan*/  ipmidriver_mutex ; 
 scalar_t__ jiffies ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bmc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int platform_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  release_bmc_device ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int __ipmi_bmc_register(struct ipmi_smi *intf,
			       struct ipmi_device_id *id,
			       bool guid_set, guid_t *guid, int intf_num)
{
	int               rv;
	struct bmc_device *bmc;
	struct bmc_device *old_bmc;

	/*
	 * platform_device_register() can cause bmc_reg_mutex to
	 * be claimed because of the is_visible functions of
	 * the attributes.  Eliminate possible recursion and
	 * release the lock.
	 */
	intf->in_bmc_register = true;
	mutex_unlock(&intf->bmc_reg_mutex);

	/*
	 * Try to find if there is an bmc_device struct
	 * representing the interfaced BMC already
	 */
	mutex_lock(&ipmidriver_mutex);
	if (guid_set)
		old_bmc = ipmi_find_bmc_guid(&ipmidriver.driver, guid);
	else
		old_bmc = ipmi_find_bmc_prod_dev_id(&ipmidriver.driver,
						    id->product_id,
						    id->device_id);

	/*
	 * If there is already an bmc_device, free the new one,
	 * otherwise register the new BMC device
	 */
	if (old_bmc) {
		bmc = old_bmc;
		/*
		 * Note: old_bmc already has usecount incremented by
		 * the BMC find functions.
		 */
		intf->bmc = old_bmc;
		mutex_lock(&bmc->dyn_mutex);
		list_add_tail(&intf->bmc_link, &bmc->intfs);
		mutex_unlock(&bmc->dyn_mutex);

		dev_info(intf->si_dev,
			 "interfacing existing BMC (man_id: 0x%6.6x, prod_id: 0x%4.4x, dev_id: 0x%2.2x)\n",
			 bmc->id.manufacturer_id,
			 bmc->id.product_id,
			 bmc->id.device_id);
	} else {
		bmc = kzalloc(sizeof(*bmc), GFP_KERNEL);
		if (!bmc) {
			rv = -ENOMEM;
			goto out;
		}
		INIT_LIST_HEAD(&bmc->intfs);
		mutex_init(&bmc->dyn_mutex);
		INIT_WORK(&bmc->remove_work, cleanup_bmc_work);

		bmc->id = *id;
		bmc->dyn_id_set = 1;
		bmc->dyn_guid_set = guid_set;
		bmc->guid = *guid;
		bmc->dyn_id_expiry = jiffies + IPMI_DYN_DEV_ID_EXPIRY;

		bmc->pdev.name = "ipmi_bmc";

		rv = ida_simple_get(&ipmi_bmc_ida, 0, 0, GFP_KERNEL);
		if (rv < 0)
			goto out;
		bmc->pdev.dev.driver = &ipmidriver.driver;
		bmc->pdev.id = rv;
		bmc->pdev.dev.release = release_bmc_device;
		bmc->pdev.dev.type = &bmc_device_type;
		kref_init(&bmc->usecount);

		intf->bmc = bmc;
		mutex_lock(&bmc->dyn_mutex);
		list_add_tail(&intf->bmc_link, &bmc->intfs);
		mutex_unlock(&bmc->dyn_mutex);

		rv = platform_device_register(&bmc->pdev);
		if (rv) {
			dev_err(intf->si_dev,
				"Unable to register bmc device: %d\n",
				rv);
			goto out_list_del;
		}

		dev_info(intf->si_dev,
			 "Found new BMC (man_id: 0x%6.6x, prod_id: 0x%4.4x, dev_id: 0x%2.2x)\n",
			 bmc->id.manufacturer_id,
			 bmc->id.product_id,
			 bmc->id.device_id);
	}

	/*
	 * create symlink from system interface device to bmc device
	 * and back.
	 */
	rv = sysfs_create_link(&intf->si_dev->kobj, &bmc->pdev.dev.kobj, "bmc");
	if (rv) {
		dev_err(intf->si_dev, "Unable to create bmc symlink: %d\n", rv);
		goto out_put_bmc;
	}

	if (intf_num == -1)
		intf_num = intf->intf_num;
	intf->my_dev_name = kasprintf(GFP_KERNEL, "ipmi%d", intf_num);
	if (!intf->my_dev_name) {
		rv = -ENOMEM;
		dev_err(intf->si_dev, "Unable to allocate link from BMC: %d\n",
			rv);
		goto out_unlink1;
	}

	rv = sysfs_create_link(&bmc->pdev.dev.kobj, &intf->si_dev->kobj,
			       intf->my_dev_name);
	if (rv) {
		kfree(intf->my_dev_name);
		intf->my_dev_name = NULL;
		dev_err(intf->si_dev, "Unable to create symlink to bmc: %d\n",
			rv);
		goto out_free_my_dev_name;
	}

	intf->bmc_registered = true;

out:
	mutex_unlock(&ipmidriver_mutex);
	mutex_lock(&intf->bmc_reg_mutex);
	intf->in_bmc_register = false;
	return rv;


out_free_my_dev_name:
	kfree(intf->my_dev_name);
	intf->my_dev_name = NULL;

out_unlink1:
	sysfs_remove_link(&intf->si_dev->kobj, "bmc");

out_put_bmc:
	mutex_lock(&bmc->dyn_mutex);
	list_del(&intf->bmc_link);
	mutex_unlock(&bmc->dyn_mutex);
	intf->bmc = &intf->tmp_bmc;
	kref_put(&bmc->usecount, cleanup_bmc_device);
	goto out;

out_list_del:
	mutex_lock(&bmc->dyn_mutex);
	list_del(&intf->bmc_link);
	mutex_unlock(&bmc->dyn_mutex);
	intf->bmc = &intf->tmp_bmc;
	put_device(&bmc->pdev.dev);
	goto out;
}