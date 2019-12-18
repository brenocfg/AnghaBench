#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct format_opts {scalar_t__ last; scalar_t__ first; } ;
struct cmdline_opts {int use_set; } ;
struct buf_pr {char* buf; } ;
typedef  int /*<<< orphan*/  rulenum ;
struct TYPE_3__ {char rule; } ;
typedef  TYPE_1__ ipfw_dyn_rule ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,...) ; 
 int /*<<< orphan*/  bp_flush (struct buf_pr*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  show_dyn_state (struct cmdline_opts*,struct format_opts*,struct buf_pr*,TYPE_1__*) ; 

__attribute__((used)) static void
list_dyn_state(struct cmdline_opts *co, struct format_opts *fo,
    void *_arg, void *_state)
{
	uint16_t rulenum;
	uint8_t set;
	ipfw_dyn_rule *d;
	struct buf_pr *bp;

	d = (ipfw_dyn_rule *)_state;
	bp = (struct buf_pr *)_arg;

	bcopy(&d->rule, &rulenum, sizeof(rulenum));
	if (rulenum > fo->last)
		return;
	if (co->use_set) {
		bcopy((char *)&d->rule + sizeof(uint16_t),
		      &set, sizeof(uint8_t));
		if (set != co->use_set - 1)
			return;
	}
	if (rulenum >= fo->first) {
		show_dyn_state(co, fo, bp, d);
		printf("%s\n", bp->buf);
		bp_flush(bp);
	}
}