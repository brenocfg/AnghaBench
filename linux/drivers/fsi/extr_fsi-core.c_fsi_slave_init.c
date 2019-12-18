#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct TYPE_7__ {scalar_t__ of_node; int /*<<< orphan*/  devt; int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; } ;
struct fsi_slave {int link; int t_send_delay; int t_echo_delay; int chip_id; TYPE_1__ dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  cdev_idx; int /*<<< orphan*/  size; scalar_t__ id; struct fsi_master* master; void* cfam_id; } ;
struct fsi_master {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* link_config ) (struct fsi_master*,int,int,int) ;int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  llmode ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ FSI_LLMODE ; 
 int /*<<< orphan*/  FSI_LLMODE_ASYNC ; 
 int FSI_MASTER_FLAG_SWCLOCK ; 
 scalar_t__ FSI_SLAVE_BASE ; 
 int /*<<< orphan*/  FSI_SLAVE_SIZE_23b ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __fsi_get_new_minor (struct fsi_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfam_fops ; 
 int /*<<< orphan*/  cfam_type ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ crc4 (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int,...) ; 
 int device_create_bin_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  fsi_dev_cfam ; 
 int /*<<< orphan*/  fsi_free_minor (int /*<<< orphan*/ ) ; 
 int fsi_master_read (struct fsi_master*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fsi_master_write (struct fsi_master*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ fsi_slave_find_of_node (struct fsi_master*,int,scalar_t__) ; 
 int /*<<< orphan*/  fsi_slave_raw_attr ; 
 int /*<<< orphan*/  fsi_slave_release ; 
 int fsi_slave_scan (struct fsi_slave*) ; 
 int fsi_slave_set_smode (struct fsi_slave*) ; 
 int /*<<< orphan*/  kfree (struct fsi_slave*) ; 
 struct fsi_slave* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 
 int /*<<< orphan*/  of_property_read_u32 (scalar_t__,char*,void**) ; 
 int /*<<< orphan*/  stub1 (struct fsi_master*,int,int,int) ; 

__attribute__((used)) static int fsi_slave_init(struct fsi_master *master, int link, uint8_t id)
{
	uint32_t cfam_id;
	struct fsi_slave *slave;
	uint8_t crc;
	__be32 data, llmode;
	int rc;

	/* Currently, we only support single slaves on a link, and use the
	 * full 23-bit address range
	 */
	if (id != 0)
		return -EINVAL;

	rc = fsi_master_read(master, link, id, 0, &data, sizeof(data));
	if (rc) {
		dev_dbg(&master->dev, "can't read slave %02x:%02x %d\n",
				link, id, rc);
		return -ENODEV;
	}
	cfam_id = be32_to_cpu(data);

	crc = crc4(0, cfam_id, 32);
	if (crc) {
		dev_warn(&master->dev, "slave %02x:%02x invalid cfam id CRC!\n",
				link, id);
		return -EIO;
	}

	dev_dbg(&master->dev, "fsi: found chip %08x at %02x:%02x:%02x\n",
			cfam_id, master->idx, link, id);

	/* If we're behind a master that doesn't provide a self-running bus
	 * clock, put the slave into async mode
	 */
	if (master->flags & FSI_MASTER_FLAG_SWCLOCK) {
		llmode = cpu_to_be32(FSI_LLMODE_ASYNC);
		rc = fsi_master_write(master, link, id,
				FSI_SLAVE_BASE + FSI_LLMODE,
				&llmode, sizeof(llmode));
		if (rc)
			dev_warn(&master->dev,
				"can't set llmode on slave:%02x:%02x %d\n",
				link, id, rc);
	}

	/* We can communicate with a slave; create the slave device and
	 * register.
	 */
	slave = kzalloc(sizeof(*slave), GFP_KERNEL);
	if (!slave)
		return -ENOMEM;

	dev_set_name(&slave->dev, "slave@%02x:%02x", link, id);
	slave->dev.type = &cfam_type;
	slave->dev.parent = &master->dev;
	slave->dev.of_node = fsi_slave_find_of_node(master, link, id);
	slave->dev.release = fsi_slave_release;
	device_initialize(&slave->dev);
	slave->cfam_id = cfam_id;
	slave->master = master;
	slave->link = link;
	slave->id = id;
	slave->size = FSI_SLAVE_SIZE_23b;
	slave->t_send_delay = 16;
	slave->t_echo_delay = 16;

	/* Get chip ID if any */
	slave->chip_id = -1;
	if (slave->dev.of_node) {
		uint32_t prop;
		if (!of_property_read_u32(slave->dev.of_node, "chip-id", &prop))
			slave->chip_id = prop;

	}

	rc = fsi_slave_set_smode(slave);
	if (rc) {
		dev_warn(&master->dev,
				"can't set smode on slave:%02x:%02x %d\n",
				link, id, rc);
		goto err_free;
	}

	/* Allocate a minor in the FSI space */
	rc = __fsi_get_new_minor(slave, fsi_dev_cfam, &slave->dev.devt,
				 &slave->cdev_idx);
	if (rc)
		goto err_free;

	/* Create chardev for userspace access */
	cdev_init(&slave->cdev, &cfam_fops);
	rc = cdev_device_add(&slave->cdev, &slave->dev);
	if (rc) {
		dev_err(&slave->dev, "Error %d creating slave device\n", rc);
		goto err_free_ida;
	}

	/* Now that we have the cdev registered with the core, any fatal
	 * failures beyond this point will need to clean up through
	 * cdev_device_del(). Fortunately though, nothing past here is fatal.
	 */

	if (master->link_config)
		master->link_config(master, link,
				    slave->t_send_delay,
				    slave->t_echo_delay);

	/* Legacy raw file -> to be removed */
	rc = device_create_bin_file(&slave->dev, &fsi_slave_raw_attr);
	if (rc)
		dev_warn(&slave->dev, "failed to create raw attr: %d\n", rc);


	rc = fsi_slave_scan(slave);
	if (rc)
		dev_dbg(&master->dev, "failed during slave scan with: %d\n",
				rc);

	return 0;

err_free_ida:
	fsi_free_minor(slave->dev.devt);
err_free:
	of_node_put(slave->dev.of_node);
	kfree(slave);
	return rc;
}