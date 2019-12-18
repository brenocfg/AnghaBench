#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t si_type; size_t addr_space; int (* io_setup ) (TYPE_1__*) ;int /*<<< orphan*/  (* io_cleanup ) (TYPE_1__*) ;TYPE_6__* dev; int /*<<< orphan*/  slave_addr; scalar_t__ irq; scalar_t__ addr_source; int /*<<< orphan*/  io_size; int /*<<< orphan*/  addr_data; } ;
struct smi_info {int run_to_completion; int interrupt_disabled; int has_event_buffer; int dev_group_added; TYPE_1__ io; int /*<<< orphan*/  req_events; int /*<<< orphan*/  need_watch; int /*<<< orphan*/ * stats; int /*<<< orphan*/ * curr_msg; int /*<<< orphan*/ * waiting_msg; int /*<<< orphan*/  si_sm; TYPE_4__* handlers; int /*<<< orphan*/  si_num; } ;
struct TYPE_14__ {int /*<<< orphan*/ * init_name; } ;
struct TYPE_13__ {scalar_t__ (* detect ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init_data ) (int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  (* size ) () ;} ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SI_BT 130 
#define  SI_KCS 129 
 int SI_NUM_STATS ; 
#define  SI_SMIC 128 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * addr_space_to_str ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_4__ bt_smi_handlers ; 
 int /*<<< orphan*/  check_for_broken_irqs (struct smi_info*) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_6__*,struct smi_info*) ; 
 int device_add_group (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handlers ; 
 int /*<<< orphan*/  ipmi_addr_src_to_str (scalar_t__) ; 
 int ipmi_register_smi (int /*<<< orphan*/ *,struct smi_info*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_si_dev_attr_group ; 
 TYPE_4__ kcs_smi_handlers ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setup_oem_data_handler (struct smi_info*) ; 
 int /*<<< orphan*/  setup_xaction_handlers (struct smi_info*) ; 
 int /*<<< orphan*/ * si_to_str ; 
 int /*<<< orphan*/  smi_num ; 
 TYPE_4__ smic_smi_handlers ; 
 int /*<<< orphan*/  start_clear_flags (struct smi_info*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int stub3 (TYPE_1__*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*) ; 
 int try_enable_event_buffer (struct smi_info*) ; 
 int try_get_dev_id (struct smi_info*) ; 

__attribute__((used)) static int try_smi_init(struct smi_info *new_smi)
{
	int rv = 0;
	int i;

	pr_info("Trying %s-specified %s state machine at %s address 0x%lx, slave address 0x%x, irq %d\n",
		ipmi_addr_src_to_str(new_smi->io.addr_source),
		si_to_str[new_smi->io.si_type],
		addr_space_to_str[new_smi->io.addr_space],
		new_smi->io.addr_data,
		new_smi->io.slave_addr, new_smi->io.irq);

	switch (new_smi->io.si_type) {
	case SI_KCS:
		new_smi->handlers = &kcs_smi_handlers;
		break;

	case SI_SMIC:
		new_smi->handlers = &smic_smi_handlers;
		break;

	case SI_BT:
		new_smi->handlers = &bt_smi_handlers;
		break;

	default:
		/* No support for anything else yet. */
		rv = -EIO;
		goto out_err;
	}

	new_smi->si_num = smi_num;

	/* Do this early so it's available for logs. */
	if (!new_smi->io.dev) {
		pr_err("IPMI interface added with no device\n");
		rv = EIO;
		goto out_err;
	}

	/* Allocate the state machine's data and initialize it. */
	new_smi->si_sm = kmalloc(new_smi->handlers->size(), GFP_KERNEL);
	if (!new_smi->si_sm) {
		rv = -ENOMEM;
		goto out_err;
	}
	new_smi->io.io_size = new_smi->handlers->init_data(new_smi->si_sm,
							   &new_smi->io);

	/* Now that we know the I/O size, we can set up the I/O. */
	rv = new_smi->io.io_setup(&new_smi->io);
	if (rv) {
		dev_err(new_smi->io.dev, "Could not set up I/O space\n");
		goto out_err;
	}

	/* Do low-level detection first. */
	if (new_smi->handlers->detect(new_smi->si_sm)) {
		if (new_smi->io.addr_source)
			dev_err(new_smi->io.dev,
				"Interface detection failed\n");
		rv = -ENODEV;
		goto out_err;
	}

	/*
	 * Attempt a get device id command.  If it fails, we probably
	 * don't have a BMC here.
	 */
	rv = try_get_dev_id(new_smi);
	if (rv) {
		if (new_smi->io.addr_source)
			dev_err(new_smi->io.dev,
			       "There appears to be no BMC at this location\n");
		goto out_err;
	}

	setup_oem_data_handler(new_smi);
	setup_xaction_handlers(new_smi);
	check_for_broken_irqs(new_smi);

	new_smi->waiting_msg = NULL;
	new_smi->curr_msg = NULL;
	atomic_set(&new_smi->req_events, 0);
	new_smi->run_to_completion = false;
	for (i = 0; i < SI_NUM_STATS; i++)
		atomic_set(&new_smi->stats[i], 0);

	new_smi->interrupt_disabled = true;
	atomic_set(&new_smi->need_watch, 0);

	rv = try_enable_event_buffer(new_smi);
	if (rv == 0)
		new_smi->has_event_buffer = true;

	/*
	 * Start clearing the flags before we enable interrupts or the
	 * timer to avoid racing with the timer.
	 */
	start_clear_flags(new_smi);

	/*
	 * IRQ is defined to be set when non-zero.  req_events will
	 * cause a global flags check that will enable interrupts.
	 */
	if (new_smi->io.irq) {
		new_smi->interrupt_disabled = false;
		atomic_set(&new_smi->req_events, 1);
	}

	dev_set_drvdata(new_smi->io.dev, new_smi);
	rv = device_add_group(new_smi->io.dev, &ipmi_si_dev_attr_group);
	if (rv) {
		dev_err(new_smi->io.dev,
			"Unable to add device attributes: error %d\n",
			rv);
		goto out_err;
	}
	new_smi->dev_group_added = true;

	rv = ipmi_register_smi(&handlers,
			       new_smi,
			       new_smi->io.dev,
			       new_smi->io.slave_addr);
	if (rv) {
		dev_err(new_smi->io.dev,
			"Unable to register device: error %d\n",
			rv);
		goto out_err;
	}

	/* Don't increment till we know we have succeeded. */
	smi_num++;

	dev_info(new_smi->io.dev, "IPMI %s interface initialized\n",
		 si_to_str[new_smi->io.si_type]);

	WARN_ON(new_smi->io.dev->init_name != NULL);

 out_err:
	if (rv && new_smi->io.io_cleanup) {
		new_smi->io.io_cleanup(&new_smi->io);
		new_smi->io.io_cleanup = NULL;
	}

	return rv;
}