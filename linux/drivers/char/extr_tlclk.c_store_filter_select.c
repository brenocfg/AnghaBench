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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_PORT_BITS (int /*<<< orphan*/ ,int,unsigned char) ; 
 int /*<<< orphan*/  TLCLK_REG0 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long) ; 
 int /*<<< orphan*/  event_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*) ; 
 int /*<<< orphan*/  strnlen (char const*,size_t) ; 

__attribute__((used)) static ssize_t store_filter_select(struct device *d,
		 struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long tmp;
	unsigned char val;
	unsigned long flags;

	sscanf(buf, "%lX", &tmp);
	dev_dbg(d, "tmp = 0x%lX\n", tmp);

	val = (unsigned char)tmp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG0, 0xfb, val);
	spin_unlock_irqrestore(&event_lock, flags);

	return strnlen(buf, count);
}