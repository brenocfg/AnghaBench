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
typedef  int u32 ;
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCRN_MQ0_CFBHL ; 
 int MQ0_CFBHL_POLY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int dcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc440spe_mq_dcr_host ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t poly_show(struct device_driver *dev, char *buf)
{
	ssize_t size = 0;
	u32 reg;

#ifdef CONFIG_440SP
	/* 440SP has fixed polynomial */
	reg = 0x4d;
#else
	reg = dcr_read(ppc440spe_mq_dcr_host, DCRN_MQ0_CFBHL);
	reg >>= MQ0_CFBHL_POLY;
	reg &= 0xFF;
#endif

	size = snprintf(buf, PAGE_SIZE, "PPC440SP(e) RAID-6 driver "
			"uses 0x1%02x polynomial.\n", reg);
	return size;
}