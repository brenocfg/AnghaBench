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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct clk sys_clk ; 
 struct clk uart_clk ; 

struct clk *clk_get(struct device *dev, const char *id)
{
	const char *lookup = id;

	if (dev)
		lookup = dev_name(dev);

	if (!strcmp(lookup, "apb:uart0"))
		return &uart_clk;
	if (!strcmp(lookup, "sys"))
		return &sys_clk;

	return ERR_PTR(-ENOENT);
}