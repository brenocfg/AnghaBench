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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct format_opts {scalar_t__ show_counters; int pcwidth; int bcwidth; int /*<<< orphan*/  dcnt; } ;
struct cmdline_opts {int use_set; } ;
struct TYPE_2__ {int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; int /*<<< orphan*/  rule; } ;
typedef  TYPE_1__ ipfw_dyn_rule ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,int*,int) ; 
 int pr_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prepare_format_dyn(struct cmdline_opts *co, struct format_opts *fo,
    void *arg, void *_state)
{
	ipfw_dyn_rule *d;
	int width;
	uint8_t set;

	d = (ipfw_dyn_rule *)_state;
	/* Count _ALL_ states */
	fo->dcnt++;

	if (fo->show_counters == 0)
		return;

	if (co->use_set) {
		/* skip states from another set */
		bcopy((char *)&d->rule + sizeof(uint16_t), &set,
		    sizeof(uint8_t));
		if (set != co->use_set - 1)
			return;
	}

	width = pr_u64(NULL, &d->pcnt, 0);
	if (width > fo->pcwidth)
		fo->pcwidth = width;

	width = pr_u64(NULL, &d->bcnt, 0);
	if (width > fo->bcwidth)
		fo->bcwidth = width;
}