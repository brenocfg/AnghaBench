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
struct intr_info {int mask; size_t stat_idx; scalar_t__ msg; scalar_t__ fatal; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ALERT (int /*<<< orphan*/ *,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  CH_WARN (int /*<<< orphan*/ *,char*,scalar_t__,unsigned int) ; 
 unsigned int t3_read_reg (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int t3_handle_intr_status(adapter_t *adapter, unsigned int reg,
				 unsigned int mask,
				 const struct intr_info *acts,
				 unsigned long *stats)
{
	int fatal = 0;
	unsigned int status = t3_read_reg(adapter, reg) & mask;

	for ( ; acts->mask; ++acts) {
		if (!(status & acts->mask)) continue;
		if (acts->fatal) {
			fatal++;
			CH_ALERT(adapter, "%s (0x%x)\n",
				 acts->msg, status & acts->mask);
			status &= ~acts->mask;
		} else if (acts->msg)
			CH_WARN(adapter, "%s (0x%x)\n",
				acts->msg, status & acts->mask);
		if (acts->stat_idx >= 0)
			stats[acts->stat_idx]++;
	}
	if (status)                           /* clear processed interrupts */
		t3_write_reg(adapter, reg, status);
	return fatal;
}