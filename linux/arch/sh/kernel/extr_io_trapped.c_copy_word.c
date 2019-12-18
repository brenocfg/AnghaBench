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

/* Variables and functions */
 unsigned long long __raw_readb (unsigned long) ; 
 unsigned long long __raw_readl (unsigned long) ; 
 unsigned long long __raw_readq (unsigned long) ; 
 unsigned long long __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  __raw_writeb (unsigned long long,unsigned long) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long long,unsigned long) ; 
 int /*<<< orphan*/  __raw_writeq (unsigned long long,unsigned long) ; 
 int /*<<< orphan*/  __raw_writew (unsigned long long,unsigned long) ; 

__attribute__((used)) static unsigned long long copy_word(unsigned long src_addr, int src_len,
				    unsigned long dst_addr, int dst_len)
{
	unsigned long long tmp = 0;

	switch (src_len) {
	case 1:
		tmp = __raw_readb(src_addr);
		break;
	case 2:
		tmp = __raw_readw(src_addr);
		break;
	case 4:
		tmp = __raw_readl(src_addr);
		break;
	case 8:
		tmp = __raw_readq(src_addr);
		break;
	}

	switch (dst_len) {
	case 1:
		__raw_writeb(tmp, dst_addr);
		break;
	case 2:
		__raw_writew(tmp, dst_addr);
		break;
	case 4:
		__raw_writel(tmp, dst_addr);
		break;
	case 8:
		__raw_writeq(tmp, dst_addr);
		break;
	}

	return tmp;
}