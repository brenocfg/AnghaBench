#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct pcmcia_device {TYPE_1__* priv; } ;
struct TYPE_8__ {int close_delay; int closing_wait; int /*<<< orphan*/ * ops; } ;
struct TYPE_7__ {int max_frame_size; int imra_value; int imrb_value; int pim_value; TYPE_2__ port; struct pcmcia_device* p_dev; int /*<<< orphan*/  idle_mode; int /*<<< orphan*/  params; int /*<<< orphan*/  netlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; int /*<<< orphan*/  task; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  MGSL_PARAMS ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDLC_TXIDLE_FLAGS ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGSLPC_MAGIC ; 
 int /*<<< orphan*/  bh_handler ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  default_params ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mgslpc_add_device (TYPE_1__*) ; 
 int mgslpc_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  mgslpc_port_ops ; 
 int /*<<< orphan*/  mgslpc_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_2__*) ; 

__attribute__((used)) static int mgslpc_probe(struct pcmcia_device *link)
{
	MGSLPC_INFO *info;
	int ret;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("mgslpc_attach\n");

	info = kzalloc(sizeof(MGSLPC_INFO), GFP_KERNEL);
	if (!info) {
		printk("Error can't allocate device instance data\n");
		return -ENOMEM;
	}

	info->magic = MGSLPC_MAGIC;
	tty_port_init(&info->port);
	info->port.ops = &mgslpc_port_ops;
	INIT_WORK(&info->task, bh_handler);
	info->max_frame_size = 4096;
	info->port.close_delay = 5*HZ/10;
	info->port.closing_wait = 30*HZ;
	init_waitqueue_head(&info->status_event_wait_q);
	init_waitqueue_head(&info->event_wait_q);
	spin_lock_init(&info->lock);
	spin_lock_init(&info->netlock);
	memcpy(&info->params,&default_params,sizeof(MGSL_PARAMS));
	info->idle_mode = HDLC_TXIDLE_FLAGS;
	info->imra_value = 0xffff;
	info->imrb_value = 0xffff;
	info->pim_value = 0xff;

	info->p_dev = link;
	link->priv = info;

	/* Initialize the struct pcmcia_device structure */

	ret = mgslpc_config(link);
	if (ret != 0)
		goto failed;

	ret = mgslpc_add_device(info);
	if (ret != 0)
		goto failed_release;

	return 0;

failed_release:
	mgslpc_release((u_long)link);
failed:
	tty_port_destroy(&info->port);
	kfree(info);
	return ret;
}