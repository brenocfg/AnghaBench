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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int b53_spi_read (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ le64_to_cpu (scalar_t__) ; 

__attribute__((used)) static int b53_spi_read48(struct b53_device *dev, u8 page, u8 reg, u64 *val)
{
	int ret;

	*val = 0;
	ret = b53_spi_read(dev, page, reg, (u8 *)val, 6);
	if (!ret)
		*val = le64_to_cpu(*val);

	return ret;
}