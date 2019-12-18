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
struct adc_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C2410_ADCCON ; 
 unsigned int S3C2410_ADCCON_ENABLE_START ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void s3c_adc_convert(struct adc_device *adc)
{
	unsigned con = readl(adc->regs + S3C2410_ADCCON);

	con |= S3C2410_ADCCON_ENABLE_START;
	writel(con, adc->regs + S3C2410_ADCCON);
}