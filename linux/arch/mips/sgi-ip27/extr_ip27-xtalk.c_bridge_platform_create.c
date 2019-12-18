#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; unsigned long start; int /*<<< orphan*/  flags; void* end; } ;
struct TYPE_3__ {char* name; unsigned long start; int /*<<< orphan*/  flags; void* end; } ;
struct xtalk_bridge_platform_data {int masterwid; unsigned long mem_offset; unsigned long io_offset; TYPE_2__ io; TYPE_1__ mem; int /*<<< orphan*/  nasid; scalar_t__ intr_addr; int /*<<< orphan*/  bridge_addr; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 scalar_t__ BIT_ULL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 unsigned long NODE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ PI_INT_PEND_MOD ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  RAW_NODE_SWIN_BASE (int /*<<< orphan*/ ,int) ; 
 void* SWIN_SIZE ; 
 int SWIN_SIZE_BITS ; 
 int /*<<< orphan*/  kfree (struct xtalk_bridge_platform_data*) ; 
 struct xtalk_bridge_platform_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_add (struct platform_device*) ; 
 int /*<<< orphan*/  platform_device_add_data (struct platform_device*,struct xtalk_bridge_platform_data*,int) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bridge_platform_create(nasid_t nasid, int widget, int masterwid)
{
	struct xtalk_bridge_platform_data *bd;
	struct platform_device *pdev;
	unsigned long offset;

	bd = kzalloc(sizeof(*bd), GFP_KERNEL);
	if (!bd)
		goto no_mem;
	pdev = platform_device_alloc("xtalk-bridge", PLATFORM_DEVID_AUTO);
	if (!pdev) {
		kfree(bd);
		goto no_mem;
	}

	offset = NODE_OFFSET(nasid);

	bd->bridge_addr = RAW_NODE_SWIN_BASE(nasid, widget);
	bd->intr_addr	= BIT_ULL(47) + 0x01800000 + PI_INT_PEND_MOD;
	bd->nasid	= nasid;
	bd->masterwid	= masterwid;

	bd->mem.name	= "Bridge PCI MEM";
	bd->mem.start	= offset + (widget << SWIN_SIZE_BITS);
	bd->mem.end	= bd->mem.start + SWIN_SIZE - 1;
	bd->mem.flags	= IORESOURCE_MEM;
	bd->mem_offset	= offset;

	bd->io.name	= "Bridge PCI IO";
	bd->io.start	= offset + (widget << SWIN_SIZE_BITS);
	bd->io.end	= bd->io.start + SWIN_SIZE - 1;
	bd->io.flags	= IORESOURCE_IO;
	bd->io_offset	= offset;

	platform_device_add_data(pdev, bd, sizeof(*bd));
	platform_device_add(pdev);
	pr_info("xtalk:n%d/%x bridge widget\n", nasid, widget);
	return;

no_mem:
	pr_warn("xtalk:n%d/%x bridge create out of memory\n", nasid, widget);
}