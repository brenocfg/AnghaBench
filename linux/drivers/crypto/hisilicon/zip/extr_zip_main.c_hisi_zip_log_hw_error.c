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
typedef  int u32 ;
struct hisi_zip_hw_error {int int_msk; scalar_t__ msg; } ;
struct TYPE_4__ {scalar_t__ io_base; TYPE_1__* pdev; } ;
struct hisi_zip {TYPE_2__ qm; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int HZIP_CORE_INT_STATUS_M_ECC ; 
 scalar_t__ HZIP_CORE_SRAM_ECC_ERR_INFO ; 
 int SRAM_ECC_ERR_ADDR_SHIFT ; 
 int SRAM_ECC_ERR_NUM_SHIFT ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,...) ; 
 int readl (scalar_t__) ; 
 struct hisi_zip_hw_error* zip_hw_error ; 

__attribute__((used)) static void hisi_zip_log_hw_error(struct hisi_zip *hisi_zip, u32 err_sts)
{
	const struct hisi_zip_hw_error *err = zip_hw_error;
	struct device *dev = &hisi_zip->qm.pdev->dev;
	u32 err_val;

	while (err->msg) {
		if (err->int_msk & err_sts) {
			dev_warn(dev, "%s [error status=0x%x] found\n",
				 err->msg, err->int_msk);

			if (HZIP_CORE_INT_STATUS_M_ECC & err->int_msk) {
				err_val = readl(hisi_zip->qm.io_base +
						HZIP_CORE_SRAM_ECC_ERR_INFO);
				dev_warn(dev, "hisi-zip multi ecc sram num=0x%x\n",
					 ((err_val >> SRAM_ECC_ERR_NUM_SHIFT) &
					  0xFF));
				dev_warn(dev, "hisi-zip multi ecc sram addr=0x%x\n",
					 (err_val >> SRAM_ECC_ERR_ADDR_SHIFT));
			}
		}
		err++;
	}
}