#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct moxtet {int* modules; int /*<<< orphan*/  dev; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  cnts ;
struct TYPE_2__ {int desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int TURRIS_MOX_CPU_ID_EMMC ; 
 int TURRIS_MOX_CPU_ID_SD ; 
 int TURRIS_MOX_MAX_MODULES ; 
 int TURRIS_MOX_MODULE_LAST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mox_module_known (int) ; 
 TYPE_1__* mox_module_table ; 
 scalar_t__ moxtet_set_irq (struct moxtet*,int,int,int /*<<< orphan*/ ) ; 
 int spi_read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int moxtet_find_topology(struct moxtet *moxtet)
{
	u8 buf[TURRIS_MOX_MAX_MODULES];
	int cnts[TURRIS_MOX_MODULE_LAST];
	int i, ret;

	memset(cnts, 0, sizeof(cnts));

	ret = spi_read(to_spi_device(moxtet->dev), buf, TURRIS_MOX_MAX_MODULES);
	if (ret < 0)
		return ret;

	if (buf[0] == TURRIS_MOX_CPU_ID_EMMC) {
		dev_info(moxtet->dev, "Found MOX A (eMMC CPU) module\n");
	} else if (buf[0] == TURRIS_MOX_CPU_ID_SD) {
		dev_info(moxtet->dev, "Found MOX A (CPU) module\n");
	} else {
		dev_err(moxtet->dev, "Invalid Turris MOX A CPU module 0x%02x\n",
			buf[0]);
		return -ENODEV;
	}

	moxtet->count = 0;

	for (i = 1; i < TURRIS_MOX_MAX_MODULES; ++i) {
		int id;

		if (buf[i] == 0xff)
			break;

		id = buf[i] & 0xf;

		moxtet->modules[i-1] = id;
		++moxtet->count;

		if (mox_module_known(id)) {
			dev_info(moxtet->dev, "Found %s module\n",
				 mox_module_table[id].desc);

			if (moxtet_set_irq(moxtet, i-1, id, cnts[id]++) < 0)
				dev_err(moxtet->dev,
					"  Cannot set IRQ for module %s\n",
					mox_module_table[id].desc);
		} else {
			dev_warn(moxtet->dev,
				 "Unknown Moxtet module found (ID 0x%02x)\n",
				 id);
		}
	}

	return 0;
}