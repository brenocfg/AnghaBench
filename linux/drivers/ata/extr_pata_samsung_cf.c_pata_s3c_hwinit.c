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
struct s3c_ide_platdata {int dummy; } ;
struct s3c_ide_info {int cpu_type; scalar_t__ ide_addr; int /*<<< orphan*/  sfr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ S3C_ATA_IRQ ; 
 scalar_t__ S3C_ATA_IRQ_MSK ; 
#define  TYPE_S3C64XX 129 
#define  TYPE_S5PV210 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pata_s3c_cfg_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pata_s3c_enable (scalar_t__,int) ; 
 int /*<<< orphan*/  pata_s3c_set_endian (scalar_t__,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void pata_s3c_hwinit(struct s3c_ide_info *info,
				struct s3c_ide_platdata *pdata)
{
	switch (info->cpu_type) {
	case TYPE_S3C64XX:
		/* Configure as big endian */
		pata_s3c_cfg_mode(info->sfr_addr);
		pata_s3c_set_endian(info->ide_addr, 1);
		pata_s3c_enable(info->ide_addr, true);
		msleep(100);

		/* Remove IRQ Status */
		writel(0x1f, info->ide_addr + S3C_ATA_IRQ);
		writel(0x1b, info->ide_addr + S3C_ATA_IRQ_MSK);
		break;

	case TYPE_S5PV210:
		/* Configure as little endian */
		pata_s3c_set_endian(info->ide_addr, 0);
		pata_s3c_enable(info->ide_addr, true);
		msleep(100);

		/* Remove IRQ Status */
		writel(0x3f, info->ide_addr + S3C_ATA_IRQ);
		writel(0x3f, info->ide_addr + S3C_ATA_IRQ_MSK);
		break;

	default:
		BUG();
	}
}