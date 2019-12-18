#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ace_device {int id; scalar_t__ bus_width; int media_change; scalar_t__ physaddr; int /*<<< orphan*/  dev; int /*<<< orphan*/  baseaddr; int /*<<< orphan*/  tag_set; TYPE_2__* queue; TYPE_1__* gd; scalar_t__ irq; int /*<<< orphan*/ * reg_ops; int /*<<< orphan*/  stall_timer; int /*<<< orphan*/  fsm_tasklet; int /*<<< orphan*/  rq_list; int /*<<< orphan*/  id_completion; int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {struct ace_device* queuedata; } ;
struct TYPE_11__ {int first_minor; TYPE_2__* queue; int /*<<< orphan*/  disk_name; struct ace_device* private_data; int /*<<< orphan*/  events; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_BUSMODE ; 
 scalar_t__ ACE_BUS_WIDTH_16 ; 
 int /*<<< orphan*/  ACE_CTRL ; 
 int ACE_CTRL_DATABUFRDYIRQ ; 
 int ACE_CTRL_ERRORIRQ ; 
 int ACE_CTRL_FORCECFGMODE ; 
 int ACE_NUM_MINORS ; 
 int /*<<< orphan*/  ACE_VERSION ; 
 int /*<<< orphan*/  BLK_BOUNCE_HIGH ; 
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 int /*<<< orphan*/  DISK_EVENT_MEDIA_CHANGE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  ace_fops ; 
 int /*<<< orphan*/  ace_fsm_tasklet ; 
 int ace_in (struct ace_device*,int /*<<< orphan*/ ) ; 
 int ace_in_le16 (struct ace_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ace_interrupt ; 
 int /*<<< orphan*/  ace_major ; 
 int /*<<< orphan*/  ace_mq_ops ; 
 int /*<<< orphan*/  ace_out (struct ace_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ace_out_8 (struct ace_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ace_out_le16 (struct ace_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ace_reg_8_ops ; 
 int /*<<< orphan*/  ace_reg_be16_ops ; 
 int /*<<< orphan*/  ace_reg_le16_ops ; 
 int /*<<< orphan*/  ace_revalidate_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  ace_stall_timer ; 
 int /*<<< orphan*/  add_disk (TYPE_1__*) ; 
 TYPE_1__* alloc_disk (int) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 TYPE_2__* blk_mq_init_sq_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ace_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ace_setup(struct ace_device *ace)
{
	u16 version;
	u16 val;
	int rc;

	dev_dbg(ace->dev, "ace_setup(ace=0x%p)\n", ace);
	dev_dbg(ace->dev, "physaddr=0x%llx irq=%i\n",
		(unsigned long long)ace->physaddr, ace->irq);

	spin_lock_init(&ace->lock);
	init_completion(&ace->id_completion);
	INIT_LIST_HEAD(&ace->rq_list);

	/*
	 * Map the device
	 */
	ace->baseaddr = ioremap(ace->physaddr, 0x80);
	if (!ace->baseaddr)
		goto err_ioremap;

	/*
	 * Initialize the state machine tasklet and stall timer
	 */
	tasklet_init(&ace->fsm_tasklet, ace_fsm_tasklet, (unsigned long)ace);
	timer_setup(&ace->stall_timer, ace_stall_timer, 0);

	/*
	 * Initialize the request queue
	 */
	ace->queue = blk_mq_init_sq_queue(&ace->tag_set, &ace_mq_ops, 2,
						BLK_MQ_F_SHOULD_MERGE);
	if (IS_ERR(ace->queue)) {
		rc = PTR_ERR(ace->queue);
		ace->queue = NULL;
		goto err_blk_initq;
	}
	ace->queue->queuedata = ace;

	blk_queue_logical_block_size(ace->queue, 512);
	blk_queue_bounce_limit(ace->queue, BLK_BOUNCE_HIGH);

	/*
	 * Allocate and initialize GD structure
	 */
	ace->gd = alloc_disk(ACE_NUM_MINORS);
	if (!ace->gd)
		goto err_alloc_disk;

	ace->gd->major = ace_major;
	ace->gd->first_minor = ace->id * ACE_NUM_MINORS;
	ace->gd->fops = &ace_fops;
	ace->gd->events = DISK_EVENT_MEDIA_CHANGE;
	ace->gd->queue = ace->queue;
	ace->gd->private_data = ace;
	snprintf(ace->gd->disk_name, 32, "xs%c", ace->id + 'a');

	/* set bus width */
	if (ace->bus_width == ACE_BUS_WIDTH_16) {
		/* 0x0101 should work regardless of endianess */
		ace_out_le16(ace, ACE_BUSMODE, 0x0101);

		/* read it back to determine endianess */
		if (ace_in_le16(ace, ACE_BUSMODE) == 0x0001)
			ace->reg_ops = &ace_reg_le16_ops;
		else
			ace->reg_ops = &ace_reg_be16_ops;
	} else {
		ace_out_8(ace, ACE_BUSMODE, 0x00);
		ace->reg_ops = &ace_reg_8_ops;
	}

	/* Make sure version register is sane */
	version = ace_in(ace, ACE_VERSION);
	if ((version == 0) || (version == 0xFFFF))
		goto err_read;

	/* Put sysace in a sane state by clearing most control reg bits */
	ace_out(ace, ACE_CTRL, ACE_CTRL_FORCECFGMODE |
		ACE_CTRL_DATABUFRDYIRQ | ACE_CTRL_ERRORIRQ);

	/* Now we can hook up the irq handler */
	if (ace->irq) {
		rc = request_irq(ace->irq, ace_interrupt, 0, "systemace", ace);
		if (rc) {
			/* Failure - fall back to polled mode */
			dev_err(ace->dev, "request_irq failed\n");
			ace->irq = 0;
		}
	}

	/* Enable interrupts */
	val = ace_in(ace, ACE_CTRL);
	val |= ACE_CTRL_DATABUFRDYIRQ | ACE_CTRL_ERRORIRQ;
	ace_out(ace, ACE_CTRL, val);

	/* Print the identification */
	dev_info(ace->dev, "Xilinx SystemACE revision %i.%i.%i\n",
		 (version >> 12) & 0xf, (version >> 8) & 0x0f, version & 0xff);
	dev_dbg(ace->dev, "physaddr 0x%llx, mapped to 0x%p, irq=%i\n",
		(unsigned long long) ace->physaddr, ace->baseaddr, ace->irq);

	ace->media_change = 1;
	ace_revalidate_disk(ace->gd);

	/* Make the sysace device 'live' */
	add_disk(ace->gd);

	return 0;

err_read:
	/* prevent double queue cleanup */
	ace->gd->queue = NULL;
	put_disk(ace->gd);
err_alloc_disk:
	blk_cleanup_queue(ace->queue);
	blk_mq_free_tag_set(&ace->tag_set);
err_blk_initq:
	iounmap(ace->baseaddr);
err_ioremap:
	dev_info(ace->dev, "xsysace: error initializing device at 0x%llx\n",
		 (unsigned long long) ace->physaddr);
	return -ENOMEM;
}