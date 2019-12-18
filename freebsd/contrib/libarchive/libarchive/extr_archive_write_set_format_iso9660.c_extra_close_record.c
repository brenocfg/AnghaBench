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
struct ctl_extr_rec {int cur_len; int dr_len; int /*<<< orphan*/  extr_off; int /*<<< orphan*/  extr_loc; int /*<<< orphan*/ * ce_ptr; scalar_t__ use_extr; scalar_t__* bp; } ;

/* Variables and functions */
 int /*<<< orphan*/  extra_tell_used_size (struct ctl_extr_rec*,int) ; 
 int /*<<< orphan*/  set_SUSP_CE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
extra_close_record(struct ctl_extr_rec *ctl, int ce_size)
{
	int padding = 0;

	if (ce_size > 0)
		extra_tell_used_size(ctl, ce_size);
	/* Padding. */
	if (ctl->cur_len & 0x01) {
		ctl->cur_len++;
		if (ctl->bp != NULL)
			ctl->bp[ctl->cur_len] = 0;
		padding = 1;
	}
	if (ctl->use_extr) {
		if (ctl->ce_ptr != NULL)
			set_SUSP_CE(ctl->ce_ptr, ctl->extr_loc,
			    ctl->extr_off, ctl->cur_len - padding);
	} else
		ctl->dr_len = ctl->cur_len;
}