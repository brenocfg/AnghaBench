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
struct task_struct {int dummy; } ;
struct dma_pool {int dummy; } ;
struct device {int dummy; } ;
struct ccp_device {int qim; size_t cmd_q_count; size_t max_q_count; char* name; int sb_count; int axcache; struct ccp_cmd_queue* cmd_q; int /*<<< orphan*/  sp; int /*<<< orphan*/  irq_tasklet; scalar_t__ use_tasklet; scalar_t__ io_regs; int /*<<< orphan*/  sb_start; struct device* dev; } ;
struct ccp_cmd_queue {unsigned int id; int int_ok; int int_err; struct dma_pool* dma_pool; struct task_struct* kthread; scalar_t__ reg_status; scalar_t__ reg_int_status; int /*<<< orphan*/  int_queue; int /*<<< orphan*/  free_slots; void* sb_ctx; void* sb_key; struct ccp_device* ccp; } ;
typedef  int /*<<< orphan*/  dma_pool_name ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_DMAPOOL_ALIGN ; 
 int /*<<< orphan*/  CCP_DMAPOOL_MAX_SIZE ; 
 scalar_t__ CMD_Q_CACHE_BASE ; 
 unsigned int CMD_Q_CACHE_INC ; 
 scalar_t__ CMD_Q_INT_STATUS_BASE ; 
 scalar_t__ CMD_Q_STATUS_BASE ; 
 unsigned int CMD_Q_STATUS_INCR ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IRQ_STATUS_REG ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 void* KSB_START ; 
 int MAX_DMAPOOL_NAME_LEN ; 
 unsigned int MAX_HW_QUEUES ; 
 int PTR_ERR (struct task_struct*) ; 
 scalar_t__ Q_MASK_REG ; 
 int /*<<< orphan*/  ccp_add_device (struct ccp_device*) ; 
 int /*<<< orphan*/  ccp_cmd_queue_thread ; 
 int /*<<< orphan*/  ccp_disable_queue_interrupts (struct ccp_device*) ; 
 int ccp_dmaengine_register (struct ccp_device*) ; 
 int /*<<< orphan*/  ccp_enable_queue_interrupts (struct ccp_device*) ; 
 int /*<<< orphan*/  ccp_get_free_slots (struct ccp_cmd_queue*) ; 
 int /*<<< orphan*/  ccp_irq_bh ; 
 int /*<<< orphan*/  ccp_irq_handler ; 
 int ccp_register_rng (struct ccp_device*) ; 
 int /*<<< orphan*/  ccp_unregister_rng (struct ccp_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*,...) ; 
 struct dma_pool* dma_pool_create (char*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (struct dma_pool*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,struct ccp_cmd_queue*,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  sp_free_ccp_irq (int /*<<< orphan*/ ,struct ccp_device*) ; 
 int sp_request_ccp_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ccp_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static int ccp_init(struct ccp_device *ccp)
{
	struct device *dev = ccp->dev;
	struct ccp_cmd_queue *cmd_q;
	struct dma_pool *dma_pool;
	char dma_pool_name[MAX_DMAPOOL_NAME_LEN];
	unsigned int qmr, i;
	int ret;

	/* Find available queues */
	ccp->qim = 0;
	qmr = ioread32(ccp->io_regs + Q_MASK_REG);
	for (i = 0; (i < MAX_HW_QUEUES) && (ccp->cmd_q_count < ccp->max_q_count); i++) {
		if (!(qmr & (1 << i)))
			continue;

		/* Allocate a dma pool for this queue */
		snprintf(dma_pool_name, sizeof(dma_pool_name), "%s_q%d",
			 ccp->name, i);
		dma_pool = dma_pool_create(dma_pool_name, dev,
					   CCP_DMAPOOL_MAX_SIZE,
					   CCP_DMAPOOL_ALIGN, 0);
		if (!dma_pool) {
			dev_err(dev, "unable to allocate dma pool\n");
			ret = -ENOMEM;
			goto e_pool;
		}

		cmd_q = &ccp->cmd_q[ccp->cmd_q_count];
		ccp->cmd_q_count++;

		cmd_q->ccp = ccp;
		cmd_q->id = i;
		cmd_q->dma_pool = dma_pool;

		/* Reserve 2 KSB regions for the queue */
		cmd_q->sb_key = KSB_START + ccp->sb_start++;
		cmd_q->sb_ctx = KSB_START + ccp->sb_start++;
		ccp->sb_count -= 2;

		/* Preset some register values and masks that are queue
		 * number dependent
		 */
		cmd_q->reg_status = ccp->io_regs + CMD_Q_STATUS_BASE +
				    (CMD_Q_STATUS_INCR * i);
		cmd_q->reg_int_status = ccp->io_regs + CMD_Q_INT_STATUS_BASE +
					(CMD_Q_STATUS_INCR * i);
		cmd_q->int_ok = 1 << (i * 2);
		cmd_q->int_err = 1 << ((i * 2) + 1);

		cmd_q->free_slots = ccp_get_free_slots(cmd_q);

		init_waitqueue_head(&cmd_q->int_queue);

		/* Build queue interrupt mask (two interrupts per queue) */
		ccp->qim |= cmd_q->int_ok | cmd_q->int_err;

#ifdef CONFIG_ARM64
		/* For arm64 set the recommended queue cache settings */
		iowrite32(ccp->axcache, ccp->io_regs + CMD_Q_CACHE_BASE +
			  (CMD_Q_CACHE_INC * i));
#endif

		dev_dbg(dev, "queue #%u available\n", i);
	}
	if (ccp->cmd_q_count == 0) {
		dev_notice(dev, "no command queues available\n");
		ret = -EIO;
		goto e_pool;
	}
	dev_notice(dev, "%u command queues available\n", ccp->cmd_q_count);

	/* Disable and clear interrupts until ready */
	ccp_disable_queue_interrupts(ccp);
	for (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		ioread32(cmd_q->reg_int_status);
		ioread32(cmd_q->reg_status);
	}
	iowrite32(ccp->qim, ccp->io_regs + IRQ_STATUS_REG);

	/* Request an irq */
	ret = sp_request_ccp_irq(ccp->sp, ccp_irq_handler, ccp->name, ccp);
	if (ret) {
		dev_err(dev, "unable to allocate an IRQ\n");
		goto e_pool;
	}

	/* Initialize the ISR tasklet? */
	if (ccp->use_tasklet)
		tasklet_init(&ccp->irq_tasklet, ccp_irq_bh,
			     (unsigned long)ccp);

	dev_dbg(dev, "Starting threads...\n");
	/* Create a kthread for each queue */
	for (i = 0; i < ccp->cmd_q_count; i++) {
		struct task_struct *kthread;

		cmd_q = &ccp->cmd_q[i];

		kthread = kthread_create(ccp_cmd_queue_thread, cmd_q,
					 "%s-q%u", ccp->name, cmd_q->id);
		if (IS_ERR(kthread)) {
			dev_err(dev, "error creating queue thread (%ld)\n",
				PTR_ERR(kthread));
			ret = PTR_ERR(kthread);
			goto e_kthread;
		}

		cmd_q->kthread = kthread;
		wake_up_process(kthread);
	}

	dev_dbg(dev, "Enabling interrupts...\n");
	/* Enable interrupts */
	ccp_enable_queue_interrupts(ccp);

	dev_dbg(dev, "Registering device...\n");
	ccp_add_device(ccp);

	ret = ccp_register_rng(ccp);
	if (ret)
		goto e_kthread;

	/* Register the DMA engine support */
	ret = ccp_dmaengine_register(ccp);
	if (ret)
		goto e_hwrng;

	return 0;

e_hwrng:
	ccp_unregister_rng(ccp);

e_kthread:
	for (i = 0; i < ccp->cmd_q_count; i++)
		if (ccp->cmd_q[i].kthread)
			kthread_stop(ccp->cmd_q[i].kthread);

	sp_free_ccp_irq(ccp->sp, ccp);

e_pool:
	for (i = 0; i < ccp->cmd_q_count; i++)
		dma_pool_destroy(ccp->cmd_q[i].dma_pool);

	return ret;
}