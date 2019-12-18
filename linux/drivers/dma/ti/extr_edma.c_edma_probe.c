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
typedef  scalar_t__ u32 ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; struct edma_soc_info* platform_data; } ;
struct platform_device {scalar_t__ id; struct device dev; } ;
struct of_phandle_args {int* args; int /*<<< orphan*/  np; } ;
struct of_device_id {scalar_t__ data; } ;
struct edma_soc_info {int default_queue; int** xbar_chans; int** queue_priority_mapping; int /*<<< orphan*/  slavecnt; int /*<<< orphan*/  slave_map; TYPE_3__* rsv; } ;
struct TYPE_7__ {int /*<<< orphan*/  fn; int /*<<< orphan*/  mapcnt; int /*<<< orphan*/  map; } ;
struct TYPE_9__ {TYPE_2__ filter; } ;
struct edma_cc {scalar_t__ id; int legacy_mode; int num_channels; int num_slots; int default_queue; int ccint; int ccerrint; scalar_t__ dummy_slot; int num_tc; TYPE_4__ dma_slave; TYPE_4__* dma_memcpy; int /*<<< orphan*/ * slave_chans; struct edma_soc_info* info; TYPE_1__* tc_list; void* slot_inuse; struct edma_soc_info* base; struct device* dev; } ;
struct device_node {int dummy; } ;
typedef  int s8 ;
typedef  int s16 ;
struct TYPE_8__ {int** rsv_slots; } ;
struct TYPE_6__ {int id; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ EDMA_BINDING_TPCC ; 
 int /*<<< orphan*/  EDMA_DRAE ; 
 int /*<<< orphan*/  EDMA_QRAE ; 
 int /*<<< orphan*/  EDMA_SLOT_ANY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct edma_soc_info*) ; 
 int PTR_ERR (struct edma_soc_info*) ; 
 int /*<<< orphan*/  bitmap_set (void*,int const,int const) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct edma_soc_info* devm_ioremap_resource (struct device*,struct resource*) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct edma_cc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct edma_cc*) ; 
 int dma_async_device_register (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_ccerr_handler ; 
 int /*<<< orphan*/  dma_irq_handler ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_paramset ; 
 scalar_t__ edma_alloc_slot (struct edma_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_assign_channel_eventq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  edma_assign_priority_to_queue (struct edma_cc*,int,int) ; 
 int /*<<< orphan*/  edma_dma_init (struct edma_cc*,int) ; 
 int /*<<< orphan*/  edma_filter_fn ; 
 int /*<<< orphan*/  edma_free_slot (struct edma_cc*,int) ; 
 int /*<<< orphan*/  edma_of_ids ; 
 int /*<<< orphan*/  edma_set_chmap (int /*<<< orphan*/ *,int) ; 
 int edma_setup_from_hw (struct device*,struct edma_soc_info*,struct edma_cc*) ; 
 struct edma_soc_info* edma_setup_info_from_dt (struct device*,int) ; 
 int /*<<< orphan*/  edma_write_array (struct edma_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_write_array2 (struct edma_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edma_write_slot (struct edma_cc*,int,int /*<<< orphan*/ *) ; 
 int irq_of_parse_and_map (struct device_node*,int) ; 
 int /*<<< orphan*/  of_dma_controller_register (struct device_node*,int /*<<< orphan*/ ,struct edma_cc*) ; 
 int /*<<< orphan*/  of_edma_xlate ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int of_parse_phandle_with_fixed_args (struct device_node*,char*,int,int,struct of_phandle_args*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct edma_cc*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  test_bit (int,void*) ; 

__attribute__((used)) static int edma_probe(struct platform_device *pdev)
{
	struct edma_soc_info	*info = pdev->dev.platform_data;
	s8			(*queue_priority_mapping)[2];
	int			i, off;
	const s16		(*rsv_slots)[2];
	const s16		(*xbar_chans)[2];
	int			irq;
	char			*irq_name;
	struct resource		*mem;
	struct device_node	*node = pdev->dev.of_node;
	struct device		*dev = &pdev->dev;
	struct edma_cc		*ecc;
	bool			legacy_mode = true;
	int ret;

	if (node) {
		const struct of_device_id *match;

		match = of_match_node(edma_of_ids, node);
		if (match && (*(u32 *)match->data) == EDMA_BINDING_TPCC)
			legacy_mode = false;

		info = edma_setup_info_from_dt(dev, legacy_mode);
		if (IS_ERR(info)) {
			dev_err(dev, "failed to get DT data\n");
			return PTR_ERR(info);
		}
	}

	if (!info)
		return -ENODEV;

	pm_runtime_enable(dev);
	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		dev_err(dev, "pm_runtime_get_sync() failed\n");
		return ret;
	}

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	ecc = devm_kzalloc(dev, sizeof(*ecc), GFP_KERNEL);
	if (!ecc)
		return -ENOMEM;

	ecc->dev = dev;
	ecc->id = pdev->id;
	ecc->legacy_mode = legacy_mode;
	/* When booting with DT the pdev->id is -1 */
	if (ecc->id < 0)
		ecc->id = 0;

	mem = platform_get_resource_byname(pdev, IORESOURCE_MEM, "edma3_cc");
	if (!mem) {
		dev_dbg(dev, "mem resource not found, using index 0\n");
		mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		if (!mem) {
			dev_err(dev, "no mem resource?\n");
			return -ENODEV;
		}
	}
	ecc->base = devm_ioremap_resource(dev, mem);
	if (IS_ERR(ecc->base))
		return PTR_ERR(ecc->base);

	platform_set_drvdata(pdev, ecc);

	/* Get eDMA3 configuration from IP */
	ret = edma_setup_from_hw(dev, info, ecc);
	if (ret)
		return ret;

	/* Allocate memory based on the information we got from the IP */
	ecc->slave_chans = devm_kcalloc(dev, ecc->num_channels,
					sizeof(*ecc->slave_chans), GFP_KERNEL);
	if (!ecc->slave_chans)
		return -ENOMEM;

	ecc->slot_inuse = devm_kcalloc(dev, BITS_TO_LONGS(ecc->num_slots),
				       sizeof(unsigned long), GFP_KERNEL);
	if (!ecc->slot_inuse)
		return -ENOMEM;

	ecc->default_queue = info->default_queue;

	if (info->rsv) {
		/* Set the reserved slots in inuse list */
		rsv_slots = info->rsv->rsv_slots;
		if (rsv_slots) {
			for (i = 0; rsv_slots[i][0] != -1; i++)
				bitmap_set(ecc->slot_inuse, rsv_slots[i][0],
					   rsv_slots[i][1]);
		}
	}

	for (i = 0; i < ecc->num_slots; i++) {
		/* Reset only unused - not reserved - paRAM slots */
		if (!test_bit(i, ecc->slot_inuse))
			edma_write_slot(ecc, i, &dummy_paramset);
	}

	/* Clear the xbar mapped channels in unused list */
	xbar_chans = info->xbar_chans;
	if (xbar_chans) {
		for (i = 0; xbar_chans[i][1] != -1; i++) {
			off = xbar_chans[i][1];
		}
	}

	irq = platform_get_irq_byname(pdev, "edma3_ccint");
	if (irq < 0 && node)
		irq = irq_of_parse_and_map(node, 0);

	if (irq >= 0) {
		irq_name = devm_kasprintf(dev, GFP_KERNEL, "%s_ccint",
					  dev_name(dev));
		ret = devm_request_irq(dev, irq, dma_irq_handler, 0, irq_name,
				       ecc);
		if (ret) {
			dev_err(dev, "CCINT (%d) failed --> %d\n", irq, ret);
			return ret;
		}
		ecc->ccint = irq;
	}

	irq = platform_get_irq_byname(pdev, "edma3_ccerrint");
	if (irq < 0 && node)
		irq = irq_of_parse_and_map(node, 2);

	if (irq >= 0) {
		irq_name = devm_kasprintf(dev, GFP_KERNEL, "%s_ccerrint",
					  dev_name(dev));
		ret = devm_request_irq(dev, irq, dma_ccerr_handler, 0, irq_name,
				       ecc);
		if (ret) {
			dev_err(dev, "CCERRINT (%d) failed --> %d\n", irq, ret);
			return ret;
		}
		ecc->ccerrint = irq;
	}

	ecc->dummy_slot = edma_alloc_slot(ecc, EDMA_SLOT_ANY);
	if (ecc->dummy_slot < 0) {
		dev_err(dev, "Can't allocate PaRAM dummy slot\n");
		return ecc->dummy_slot;
	}

	queue_priority_mapping = info->queue_priority_mapping;

	if (!ecc->legacy_mode) {
		int lowest_priority = 0;
		struct of_phandle_args tc_args;

		ecc->tc_list = devm_kcalloc(dev, ecc->num_tc,
					    sizeof(*ecc->tc_list), GFP_KERNEL);
		if (!ecc->tc_list)
			return -ENOMEM;

		for (i = 0;; i++) {
			ret = of_parse_phandle_with_fixed_args(node, "ti,tptcs",
							       1, i, &tc_args);
			if (ret || i == ecc->num_tc)
				break;

			ecc->tc_list[i].node = tc_args.np;
			ecc->tc_list[i].id = i;
			queue_priority_mapping[i][1] = tc_args.args[0];
			if (queue_priority_mapping[i][1] > lowest_priority) {
				lowest_priority = queue_priority_mapping[i][1];
				info->default_queue = i;
			}
		}
	}

	/* Event queue priority mapping */
	for (i = 0; queue_priority_mapping[i][0] != -1; i++)
		edma_assign_priority_to_queue(ecc, queue_priority_mapping[i][0],
					      queue_priority_mapping[i][1]);

	edma_write_array2(ecc, EDMA_DRAE, 0, 0, 0x0);
	edma_write_array2(ecc, EDMA_DRAE, 0, 1, 0x0);
	edma_write_array(ecc, EDMA_QRAE, 0, 0x0);

	ecc->info = info;

	/* Init the dma device and channels */
	edma_dma_init(ecc, legacy_mode);

	for (i = 0; i < ecc->num_channels; i++) {
		/* Assign all channels to the default queue */
		edma_assign_channel_eventq(&ecc->slave_chans[i],
					   info->default_queue);
		/* Set entry slot to the dummy slot */
		edma_set_chmap(&ecc->slave_chans[i], ecc->dummy_slot);
	}

	ecc->dma_slave.filter.map = info->slave_map;
	ecc->dma_slave.filter.mapcnt = info->slavecnt;
	ecc->dma_slave.filter.fn = edma_filter_fn;

	ret = dma_async_device_register(&ecc->dma_slave);
	if (ret) {
		dev_err(dev, "slave ddev registration failed (%d)\n", ret);
		goto err_reg1;
	}

	if (ecc->dma_memcpy) {
		ret = dma_async_device_register(ecc->dma_memcpy);
		if (ret) {
			dev_err(dev, "memcpy ddev registration failed (%d)\n",
				ret);
			dma_async_device_unregister(&ecc->dma_slave);
			goto err_reg1;
		}
	}

	if (node)
		of_dma_controller_register(node, of_edma_xlate, ecc);

	dev_info(dev, "TI EDMA DMA engine driver\n");

	return 0;

err_reg1:
	edma_free_slot(ecc, ecc->dummy_slot);
	return ret;
}