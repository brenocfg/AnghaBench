#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct extr_rec* current; } ;
struct isoent {TYPE_2__ extr_rec_list; } ;
struct extr_rec {int offset; } ;
struct ctl_extr_rec {int cur_len; TYPE_1__* isoent; scalar_t__ use_extr; } ;
struct TYPE_3__ {struct isoent* parent; } ;

/* Variables and functions */

__attribute__((used)) static void
extra_tell_used_size(struct ctl_extr_rec *ctl, int size)
{
	struct isoent *isoent;
	struct extr_rec *rec;

	if (ctl->use_extr) {
		isoent = ctl->isoent->parent;
		rec = isoent->extr_rec_list.current;
		if (rec != NULL)
			rec->offset += size;
	}
	ctl->cur_len += size;
}