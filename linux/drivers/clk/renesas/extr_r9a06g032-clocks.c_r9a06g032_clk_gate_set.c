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
struct r9a06g032_priv {int /*<<< orphan*/  lock; } ;
struct r9a06g032_gate {scalar_t__ midle; scalar_t__ ready; scalar_t__ reset; scalar_t__ gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_rdesc_set (struct r9a06g032_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
r9a06g032_clk_gate_set(struct r9a06g032_priv *clocks,
		       struct r9a06g032_gate *g, int on)
{
	unsigned long flags;

	WARN_ON(!g->gate);

	spin_lock_irqsave(&clocks->lock, flags);
	clk_rdesc_set(clocks, g->gate, on);
	/* De-assert reset */
	if (g->reset)
		clk_rdesc_set(clocks, g->reset, 1);
	spin_unlock_irqrestore(&clocks->lock, flags);

	/* Hardware manual recommends 5us delay after enabling clock & reset */
	udelay(5);

	/* If the peripheral is memory mapped (i.e. an AXI slave), there is an
	 * associated SLVRDY bit in the System Controller that needs to be set
	 * so that the FlexWAY bus fabric passes on the read/write requests.
	 */
	if (g->ready || g->midle) {
		spin_lock_irqsave(&clocks->lock, flags);
		if (g->ready)
			clk_rdesc_set(clocks, g->ready, on);
		/* Clear 'Master Idle Request' bit */
		if (g->midle)
			clk_rdesc_set(clocks, g->midle, !on);
		spin_unlock_irqrestore(&clocks->lock, flags);
	}
	/* Note: We don't wait for FlexWAY Socket Connection signal */
}