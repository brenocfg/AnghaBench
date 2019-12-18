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
struct ip_fw_rule {scalar_t__ rulenum; int set; } ;
struct ip_fw_bcounter {scalar_t__ size; } ;
struct format_opts {int show_counters; int show_time; scalar_t__ last; scalar_t__ first; } ;
struct cmdline_opts {int use_set; } ;
struct buf_pr {char* buf; } ;
struct TYPE_3__ {scalar_t__ length; } ;
typedef  TYPE_1__ ipfw_obj_tlv ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bp_flush (struct buf_pr*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  show_static_rule (struct cmdline_opts*,struct format_opts*,struct buf_pr*,struct ip_fw_rule*,struct ip_fw_bcounter*) ; 

__attribute__((used)) static int
list_static_range(struct cmdline_opts *co, struct format_opts *fo,
    struct buf_pr *bp, ipfw_obj_tlv *rtlv, int rcnt)
{
	int n, seen;
	struct ip_fw_rule *r;
	struct ip_fw_bcounter *cntr;
	int c = 0;

	for (n = seen = 0; n < rcnt; n++,
	    rtlv = (ipfw_obj_tlv *)((caddr_t)rtlv + rtlv->length)) {

		if ((fo->show_counters | fo->show_time) != 0) {
			cntr = (struct ip_fw_bcounter *)(rtlv + 1);
			r = (struct ip_fw_rule *)((caddr_t)cntr + cntr->size);
		} else {
			cntr = NULL;
			r = (struct ip_fw_rule *)(rtlv + 1);
		}
		if (r->rulenum > fo->last)
			break;
		if (co->use_set && r->set != co->use_set - 1)
			continue;
		if (r->rulenum >= fo->first && r->rulenum <= fo->last) {
			show_static_rule(co, fo, bp, r, cntr);
			printf("%s", bp->buf);
			c += rtlv->length;
			bp_flush(bp);
			seen++;
		}
	}

	return (seen);
}