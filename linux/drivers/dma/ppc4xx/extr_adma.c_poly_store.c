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
struct device_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCRN_MQ0_CFBHL ; 
 size_t EINVAL ; 
 int MQ0_CFBHL_POLY ; 
 unsigned long dcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ppc440spe_mq_dcr_host ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*) ; 

__attribute__((used)) static ssize_t poly_store(struct device_driver *dev, const char *buf,
			  size_t count)
{
	unsigned long reg, val;

#ifdef CONFIG_440SP
	/* 440SP uses default 0x14D polynomial only */
	return -EINVAL;
#endif

	if (!count || count > 6)
		return -EINVAL;

	/* e.g., 0x14D or 0x11D */
	sscanf(buf, "%lx", &val);

	if (val & ~0x1FF)
		return -EINVAL;

	val &= 0xFF;
	reg = dcr_read(ppc440spe_mq_dcr_host, DCRN_MQ0_CFBHL);
	reg &= ~(0xFF << MQ0_CFBHL_POLY);
	reg |= val << MQ0_CFBHL_POLY;
	dcr_write(ppc440spe_mq_dcr_host, DCRN_MQ0_CFBHL, reg);

	return count;
}