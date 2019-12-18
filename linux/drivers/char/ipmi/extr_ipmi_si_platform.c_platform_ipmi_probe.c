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
typedef  scalar_t__ u8 ;
struct si_sm_io {int slave_addr; scalar_t__ irq; scalar_t__ addr_space; int /*<<< orphan*/  regspacing; scalar_t__ regsize; int /*<<< orphan*/  addr_data; int /*<<< orphan*/ * dev; int /*<<< orphan*/  irq_setup; scalar_t__ regshift; scalar_t__ si_type; scalar_t__ addr_source; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 scalar_t__ DEFAULT_REGSIZE ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IPMI_IO_ADDR_SPACE ; 
#define  SI_BT 131 
 scalar_t__ SI_HARDCODED ; 
#define  SI_KCS 130 
 scalar_t__ SI_LAST ; 
 scalar_t__ SI_PLATFORM ; 
 scalar_t__ SI_SMBIOS ; 
#define  SI_SMIC 129 
#define  SI_TYPE_INVALID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_property_read_u8 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  ipmi_addr_src_to_str (scalar_t__) ; 
 int /*<<< orphan*/  ipmi_get_info_from_resources (struct platform_device*,struct si_sm_io*) ; 
 int /*<<< orphan*/  ipmi_si_add_smi (struct si_sm_io*) ; 
 int /*<<< orphan*/  ipmi_std_irq_setup ; 
 int /*<<< orphan*/  memset (struct si_sm_io*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  si_trydmi ; 
 int /*<<< orphan*/  si_tryplatform ; 

__attribute__((used)) static int platform_ipmi_probe(struct platform_device *pdev)
{
	struct si_sm_io io;
	u8 type, slave_addr, addr_source, regsize, regshift;
	int rv;

	rv = device_property_read_u8(&pdev->dev, "addr-source", &addr_source);
	if (rv)
		addr_source = SI_PLATFORM;
	if (addr_source >= SI_LAST)
		return -EINVAL;

	if (addr_source == SI_SMBIOS) {
		if (!si_trydmi)
			return -ENODEV;
	} else if (addr_source != SI_HARDCODED) {
		if (!si_tryplatform)
			return -ENODEV;
	}

	rv = device_property_read_u8(&pdev->dev, "ipmi-type", &type);
	if (rv)
		return -ENODEV;

	memset(&io, 0, sizeof(io));
	io.addr_source = addr_source;
	dev_info(&pdev->dev, "probing via %s\n",
		 ipmi_addr_src_to_str(addr_source));

	switch (type) {
	case SI_KCS:
	case SI_SMIC:
	case SI_BT:
		io.si_type = type;
		break;
	case SI_TYPE_INVALID: /* User disabled this in hardcode. */
		return -ENODEV;
	default:
		dev_err(&pdev->dev, "ipmi-type property is invalid\n");
		return -EINVAL;
	}

	io.regsize = DEFAULT_REGSIZE;
	rv = device_property_read_u8(&pdev->dev, "reg-size", &regsize);
	if (!rv)
		io.regsize = regsize;

	io.regshift = 0;
	rv = device_property_read_u8(&pdev->dev, "reg-shift", &regshift);
	if (!rv)
		io.regshift = regshift;

	if (!ipmi_get_info_from_resources(pdev, &io))
		return -EINVAL;

	rv = device_property_read_u8(&pdev->dev, "slave-addr", &slave_addr);
	if (rv)
		io.slave_addr = 0x20;
	else
		io.slave_addr = slave_addr;

	io.irq = platform_get_irq(pdev, 0);
	if (io.irq > 0)
		io.irq_setup = ipmi_std_irq_setup;
	else
		io.irq = 0;

	io.dev = &pdev->dev;

	pr_info("ipmi_si: %s: %s %#lx regsize %d spacing %d irq %d\n",
		ipmi_addr_src_to_str(addr_source),
		(io.addr_space == IPMI_IO_ADDR_SPACE) ? "io" : "mem",
		io.addr_data, io.regsize, io.regspacing, io.irq);

	ipmi_si_add_smi(&io);

	return 0;
}