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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct cc_req_mgr_handle {scalar_t__ hw_queue_size; scalar_t__ min_free_hw_slots; int /*<<< orphan*/  compl_desc; int /*<<< orphan*/  dummy_comp_buff_dma; int /*<<< orphan*/  dummy_comp_buff; scalar_t__ max_used_sw_slots; int /*<<< orphan*/  comptask; int /*<<< orphan*/  compwork; int /*<<< orphan*/  workq; int /*<<< orphan*/  backlog; int /*<<< orphan*/  bl_lock; int /*<<< orphan*/  hw_lock; } ;
struct cc_drvdata {struct cc_req_mgr_handle* request_mgr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYPASS ; 
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSCRPTR_QUEUE_SRAM_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN_HW_QUEUE_SIZE ; 
 int /*<<< orphan*/  NS_BIT ; 
 scalar_t__ cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_req_mgr_fini (struct cc_drvdata*) ; 
 int /*<<< orphan*/  comp_handler ; 
 int /*<<< orphan*/  comp_work_handler ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  hw_desc_init (int /*<<< orphan*/ *) ; 
 struct cc_req_mgr_handle* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dout_dlli (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_queue_last_ind (struct cc_drvdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int cc_req_mgr_init(struct cc_drvdata *drvdata)
{
	struct cc_req_mgr_handle *req_mgr_h;
	struct device *dev = drvdata_to_dev(drvdata);
	int rc = 0;

	req_mgr_h = kzalloc(sizeof(*req_mgr_h), GFP_KERNEL);
	if (!req_mgr_h) {
		rc = -ENOMEM;
		goto req_mgr_init_err;
	}

	drvdata->request_mgr_handle = req_mgr_h;

	spin_lock_init(&req_mgr_h->hw_lock);
	spin_lock_init(&req_mgr_h->bl_lock);
	INIT_LIST_HEAD(&req_mgr_h->backlog);

#ifdef COMP_IN_WQ
	dev_dbg(dev, "Initializing completion workqueue\n");
	req_mgr_h->workq = create_singlethread_workqueue("ccree");
	if (!req_mgr_h->workq) {
		dev_err(dev, "Failed creating work queue\n");
		rc = -ENOMEM;
		goto req_mgr_init_err;
	}
	INIT_DELAYED_WORK(&req_mgr_h->compwork, comp_work_handler);
#else
	dev_dbg(dev, "Initializing completion tasklet\n");
	tasklet_init(&req_mgr_h->comptask, comp_handler,
		     (unsigned long)drvdata);
#endif
	req_mgr_h->hw_queue_size = cc_ioread(drvdata,
					     CC_REG(DSCRPTR_QUEUE_SRAM_SIZE));
	dev_dbg(dev, "hw_queue_size=0x%08X\n", req_mgr_h->hw_queue_size);
	if (req_mgr_h->hw_queue_size < MIN_HW_QUEUE_SIZE) {
		dev_err(dev, "Invalid HW queue size = %u (Min. required is %u)\n",
			req_mgr_h->hw_queue_size, MIN_HW_QUEUE_SIZE);
		rc = -ENOMEM;
		goto req_mgr_init_err;
	}
	req_mgr_h->min_free_hw_slots = req_mgr_h->hw_queue_size;
	req_mgr_h->max_used_sw_slots = 0;

	/* Allocate DMA word for "dummy" completion descriptor use */
	req_mgr_h->dummy_comp_buff =
		dma_alloc_coherent(dev, sizeof(u32),
				   &req_mgr_h->dummy_comp_buff_dma,
				   GFP_KERNEL);
	if (!req_mgr_h->dummy_comp_buff) {
		dev_err(dev, "Not enough memory to allocate DMA (%zu) dropped buffer\n",
			sizeof(u32));
		rc = -ENOMEM;
		goto req_mgr_init_err;
	}

	/* Init. "dummy" completion descriptor */
	hw_desc_init(&req_mgr_h->compl_desc);
	set_din_const(&req_mgr_h->compl_desc, 0, sizeof(u32));
	set_dout_dlli(&req_mgr_h->compl_desc, req_mgr_h->dummy_comp_buff_dma,
		      sizeof(u32), NS_BIT, 1);
	set_flow_mode(&req_mgr_h->compl_desc, BYPASS);
	set_queue_last_ind(drvdata, &req_mgr_h->compl_desc);

	return 0;

req_mgr_init_err:
	cc_req_mgr_fini(drvdata);
	return rc;
}