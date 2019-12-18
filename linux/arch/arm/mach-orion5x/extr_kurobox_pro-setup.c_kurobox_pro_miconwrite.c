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
 int /*<<< orphan*/  LSR ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  UART1_REG (int /*<<< orphan*/ ) ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  barrier () ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kurobox_pro_miconwrite(const unsigned char *buf, int count)
{
	int i = 0;

	while (count--) {
		while (!(readl(UART1_REG(LSR)) & UART_LSR_THRE))
			barrier();
		writel(buf[i++], UART1_REG(TX));
	}

	return 0;
}