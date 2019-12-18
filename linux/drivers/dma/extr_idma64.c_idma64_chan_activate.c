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
struct idma64_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LO ; 
 int IDMA64C_CFGL_CH_SUSP ; 
 int channel_readl (struct idma64_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_writel (struct idma64_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void idma64_chan_activate(struct idma64_chan *idma64c)
{
	u32 cfglo;

	cfglo = channel_readl(idma64c, CFG_LO);
	channel_writel(idma64c, CFG_LO, cfglo & ~IDMA64C_CFGL_CH_SUSP);
}