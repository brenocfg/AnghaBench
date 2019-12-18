#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ep93xx_dma_data {int dummy; } ;
struct TYPE_2__ {struct ep93xx_dma_data* private; } ;
struct ep93xx_dma_chan {scalar_t__ regs; int /*<<< orphan*/  runtime_ctrl; TYPE_1__ chan; } ;

/* Variables and functions */
 scalar_t__ M2M_CONTROL ; 
 int /*<<< orphan*/  M2M_CONTROL_DONEINT ; 
 int /*<<< orphan*/  M2M_CONTROL_ENABLE ; 
 int /*<<< orphan*/  M2M_CONTROL_NFBINT ; 
 int /*<<< orphan*/  M2M_CONTROL_PW_MASK ; 
 int /*<<< orphan*/  M2M_CONTROL_START ; 
 scalar_t__ ep93xx_dma_advance_active (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  m2m_fill_desc (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void m2m_hw_submit(struct ep93xx_dma_chan *edmac)
{
	struct ep93xx_dma_data *data = edmac->chan.private;
	u32 control = readl(edmac->regs + M2M_CONTROL);

	/*
	 * Since we allow clients to configure PW (peripheral width) we always
	 * clear PW bits here and then set them according what is given in
	 * the runtime configuration.
	 */
	control &= ~M2M_CONTROL_PW_MASK;
	control |= edmac->runtime_ctrl;

	m2m_fill_desc(edmac);
	control |= M2M_CONTROL_DONEINT;

	if (ep93xx_dma_advance_active(edmac)) {
		m2m_fill_desc(edmac);
		control |= M2M_CONTROL_NFBINT;
	}

	/*
	 * Now we can finally enable the channel. For M2M channel this must be
	 * done _after_ the BCRx registers are programmed.
	 */
	control |= M2M_CONTROL_ENABLE;
	writel(control, edmac->regs + M2M_CONTROL);

	if (!data) {
		/*
		 * For memcpy channels the software trigger must be asserted
		 * in order to start the memcpy operation.
		 */
		control |= M2M_CONTROL_START;
		writel(control, edmac->regs + M2M_CONTROL);
	}
}