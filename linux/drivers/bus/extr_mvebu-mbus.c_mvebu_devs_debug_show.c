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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct mvebu_mbus_state {TYPE_1__* soc; } ;
struct TYPE_2__ {int num_wins; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 struct mvebu_mbus_state mbus_state ; 
 int /*<<< orphan*/  mvebu_mbus_read_window (struct mvebu_mbus_state*,int,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ mvebu_mbus_window_is_remappable (struct mvebu_mbus_state*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int mvebu_devs_debug_show(struct seq_file *seq, void *v)
{
	struct mvebu_mbus_state *mbus = &mbus_state;
	int win;

	for (win = 0; win < mbus->soc->num_wins; win++) {
		u64 wbase, wremap;
		u32 wsize;
		u8 wtarget, wattr;
		int enabled;

		mvebu_mbus_read_window(mbus, win,
				       &enabled, &wbase, &wsize,
				       &wtarget, &wattr, &wremap);

		if (!enabled) {
			seq_printf(seq, "[%02d] disabled\n", win);
			continue;
		}

		seq_printf(seq, "[%02d] %016llx - %016llx : %04x:%04x",
			   win, (unsigned long long)wbase,
			   (unsigned long long)(wbase + wsize), wtarget, wattr);

		if (!is_power_of_2(wsize) ||
		    ((wbase & (u64)(wsize - 1)) != 0))
			seq_puts(seq, " (Invalid base/size!!)");

		if (mvebu_mbus_window_is_remappable(mbus, win)) {
			seq_printf(seq, " (remap %016llx)\n",
				   (unsigned long long)wremap);
		} else
			seq_printf(seq, "\n");
	}

	return 0;
}