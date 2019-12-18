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
struct fsi_master_acf {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ external_mode; } ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BREAK ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int do_copro_command (struct fsi_master_acf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_address_update (struct fsi_master_acf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fsi_master_acf* to_fsi_master_acf (struct fsi_master*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fsi_master_acf_break(struct fsi_master *_master, int link)
{
	struct fsi_master_acf *master = to_fsi_master_acf(_master);
	int rc;

	if (link != 0)
		return -ENODEV;

	mutex_lock(&master->lock);
	if (master->external_mode) {
		mutex_unlock(&master->lock);
		return -EBUSY;
	}
	dev_dbg(master->dev, "sending BREAK\n");
	rc = do_copro_command(master, CMD_BREAK);
	last_address_update(master, 0, false, 0);
	mutex_unlock(&master->lock);

	/* Wait for logic reset to take effect */
	udelay(200);

	return rc;
}