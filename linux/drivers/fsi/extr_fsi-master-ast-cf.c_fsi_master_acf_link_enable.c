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
struct fsi_master_acf {int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_enable; int /*<<< orphan*/  external_mode; } ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fsi_master_acf* to_fsi_master_acf (struct fsi_master*) ; 

__attribute__((used)) static int fsi_master_acf_link_enable(struct fsi_master *_master, int link)
{
	struct fsi_master_acf *master = to_fsi_master_acf(_master);
	int rc = -EBUSY;

	if (link != 0)
		return -ENODEV;

	mutex_lock(&master->lock);
	if (!master->external_mode) {
		gpiod_set_value(master->gpio_enable, 1);
		rc = 0;
	}
	mutex_unlock(&master->lock);

	return rc;
}