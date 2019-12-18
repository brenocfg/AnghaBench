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
typedef  void* u8 ;
struct fsi_master_acf {int /*<<< orphan*/  lock; scalar_t__ sram; void* t_echo_delay; void* t_send_delay; int /*<<< orphan*/  dev; } ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 scalar_t__ ECHO_DLY_REG ; 
 int ENODEV ; 
 scalar_t__ SEND_DLY_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*,void*) ; 
 int /*<<< orphan*/  iowrite8 (void*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fsi_master_acf* to_fsi_master_acf (struct fsi_master*) ; 

__attribute__((used)) static int fsi_master_acf_link_config(struct fsi_master *_master, int link,
				      u8 t_send_delay, u8 t_echo_delay)
{
	struct fsi_master_acf *master = to_fsi_master_acf(_master);

	if (link != 0)
		return -ENODEV;

	mutex_lock(&master->lock);
	master->t_send_delay = t_send_delay;
	master->t_echo_delay = t_echo_delay;
	dev_dbg(master->dev, "Changing delays: send=%d echo=%d\n",
		t_send_delay, t_echo_delay);
	iowrite8(master->t_send_delay, master->sram + SEND_DLY_REG);
	iowrite8(master->t_echo_delay, master->sram + ECHO_DLY_REG);
	mutex_unlock(&master->lock);

	return 0;
}