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
struct scoop_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SCOOP_GPWR ; 
 unsigned short ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (unsigned short,scalar_t__) ; 

__attribute__((used)) static void __scoop_gpio_set(struct scoop_dev *sdev,
			unsigned offset, int value)
{
	unsigned short gpwr;

	gpwr = ioread16(sdev->base + SCOOP_GPWR);
	if (value)
		gpwr |= 1 << (offset + 1);
	else
		gpwr &= ~(1 << (offset + 1));
	iowrite16(gpwr, sdev->base + SCOOP_GPWR);
}