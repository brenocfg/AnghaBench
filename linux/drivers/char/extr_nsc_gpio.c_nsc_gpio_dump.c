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
struct nsc_gpio_ops {int (* gpio_config ) (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* gpio_current ) (unsigned int) ;int /*<<< orphan*/  (* gpio_get ) (unsigned int) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,int,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 

void nsc_gpio_dump(struct nsc_gpio_ops *amp, unsigned index)
{
	/* retrieve current config w/o changing it */
	u32 config = amp->gpio_config(index, ~0, 0);

	/* user requested via 'v' command, so its INFO */
	dev_info(amp->dev, "io%02u: 0x%04x %s %s %s %s %s %s %s\tio:%d/%d\n",
		 index, config,
		 (config & 1) ? "OE" : "TS",      /* output-enabled/tristate */
		 (config & 2) ? "PP" : "OD",      /* push pull / open drain */
		 (config & 4) ? "PUE" : "PUD",    /* pull up enabled/disabled */
		 (config & 8) ? "LOCKED" : "",    /* locked / unlocked */
		 (config & 16) ? "LEVEL" : "EDGE",/* level/edge input */
		 (config & 32) ? "HI" : "LO",     /* trigger on rise/fall edge */
		 (config & 64) ? "DEBOUNCE" : "", /* debounce */

		 amp->gpio_get(index), amp->gpio_current(index));
}