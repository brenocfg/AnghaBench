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
struct vas_window {int /*<<< orphan*/  hvwc_map; } ;
struct seq_file {struct vas_window* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR ; 
 int /*<<< orphan*/  CURR_MSG_COUNT ; 
 int /*<<< orphan*/  FAULT_TX_WIN ; 
 int /*<<< orphan*/  HV_INTR_SRC_RA ; 
 int /*<<< orphan*/  LDATA_STAMP_CTL ; 
 int /*<<< orphan*/  LDMA_CACHE_CTL ; 
 int /*<<< orphan*/  LFIFO_BAR ; 
 int /*<<< orphan*/  LFIFO_SIZE ; 
 int /*<<< orphan*/  LNOTIFY_AFTER_COUNT ; 
 int /*<<< orphan*/  LNOTIFY_CTL ; 
 int /*<<< orphan*/  LNOTIFY_LPID ; 
 int /*<<< orphan*/  LNOTIFY_PID ; 
 int /*<<< orphan*/  LNOTIFY_SCOPE ; 
 int /*<<< orphan*/  LNOTIFY_TID ; 
 int /*<<< orphan*/  LPID ; 
 int /*<<< orphan*/  LRFIFO_PUSH ; 
 int /*<<< orphan*/  LRFIFO_WIN_PTR ; 
 int /*<<< orphan*/  LRX_WCRED ; 
 int /*<<< orphan*/  LRX_WCRED_ADDER ; 
 int /*<<< orphan*/  NX_UTIL_ADDER ; 
 int /*<<< orphan*/  OSU_INTR_SRC_RA ; 
 int /*<<< orphan*/  PID ; 
 int /*<<< orphan*/  PSWID ; 
 int /*<<< orphan*/  SEIDR ; 
 int /*<<< orphan*/  TX_RSVD_BUF_COUNT ; 
 int /*<<< orphan*/  TX_WCRED ; 
 int /*<<< orphan*/  TX_WCRED_ADDER ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINCTL ; 
 int /*<<< orphan*/  WIN_CTX_CACHING_CTL ; 
 int /*<<< orphan*/  WIN_STATUS ; 
 int /*<<< orphan*/  XLATE_CTL ; 
 int /*<<< orphan*/  XLATE_LPCR ; 
 int /*<<< orphan*/  XLATE_MSR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_reg (struct seq_file*,struct vas_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vas_mutex ; 

__attribute__((used)) static int hvwc_show(struct seq_file *s, void *private)
{
	struct vas_window *window = s->private;

	mutex_lock(&vas_mutex);

	/* ensure window is not unmapped */
	if (!window->hvwc_map)
		goto unlock;

	print_reg(s, window, VREG(LPID));
	print_reg(s, window, VREG(PID));
	print_reg(s, window, VREG(XLATE_MSR));
	print_reg(s, window, VREG(XLATE_LPCR));
	print_reg(s, window, VREG(XLATE_CTL));
	print_reg(s, window, VREG(AMR));
	print_reg(s, window, VREG(SEIDR));
	print_reg(s, window, VREG(FAULT_TX_WIN));
	print_reg(s, window, VREG(OSU_INTR_SRC_RA));
	print_reg(s, window, VREG(HV_INTR_SRC_RA));
	print_reg(s, window, VREG(PSWID));
	print_reg(s, window, VREG(LFIFO_BAR));
	print_reg(s, window, VREG(LDATA_STAMP_CTL));
	print_reg(s, window, VREG(LDMA_CACHE_CTL));
	print_reg(s, window, VREG(LRFIFO_PUSH));
	print_reg(s, window, VREG(CURR_MSG_COUNT));
	print_reg(s, window, VREG(LNOTIFY_AFTER_COUNT));
	print_reg(s, window, VREG(LRX_WCRED));
	print_reg(s, window, VREG(LRX_WCRED_ADDER));
	print_reg(s, window, VREG(TX_WCRED));
	print_reg(s, window, VREG(TX_WCRED_ADDER));
	print_reg(s, window, VREG(LFIFO_SIZE));
	print_reg(s, window, VREG(WINCTL));
	print_reg(s, window, VREG(WIN_STATUS));
	print_reg(s, window, VREG(WIN_CTX_CACHING_CTL));
	print_reg(s, window, VREG(TX_RSVD_BUF_COUNT));
	print_reg(s, window, VREG(LRFIFO_WIN_PTR));
	print_reg(s, window, VREG(LNOTIFY_CTL));
	print_reg(s, window, VREG(LNOTIFY_PID));
	print_reg(s, window, VREG(LNOTIFY_LPID));
	print_reg(s, window, VREG(LNOTIFY_TID));
	print_reg(s, window, VREG(LNOTIFY_SCOPE));
	print_reg(s, window, VREG(NX_UTIL_ADDER));
unlock:
	mutex_unlock(&vas_mutex);
	return 0;
}