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
typedef  scalar_t__ u64 ;
struct vas_window {int /*<<< orphan*/  winid; scalar_t__ tx_win; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,char*,void*,scalar_t__) ; 

__attribute__((used)) static inline void vas_log_write(struct vas_window *win, char *name,
			void *regptr, u64 val)
{
	if (val)
		pr_debug("%swin #%d: %s reg %p, val 0x%016llx\n",
				win->tx_win ? "Tx" : "Rx", win->winid, name,
				regptr, val);
}