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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 struct clk* clk_get_sys (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clkdev_create (struct clk*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_add_lookup_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa1111_pcmcia_gpio_table ; 

__attribute__((used)) static void lubbock_init_pcmcia(void)
{
	struct clk *clk;

	gpiod_add_lookup_table(&sa1111_pcmcia_gpio_table);

	/* Add an alias for the SA1111 PCMCIA clock */
	clk = clk_get_sys("pxa2xx-pcmcia", NULL);
	if (!IS_ERR(clk)) {
		clkdev_create(clk, NULL, "1800");
		clk_put(clk);
	}
}