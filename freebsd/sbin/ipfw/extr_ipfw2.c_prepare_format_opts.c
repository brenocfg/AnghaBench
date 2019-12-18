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
struct ip_fw_rule {int set; } ;
struct ip_fw_bcounter {int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; scalar_t__ size; } ;
struct format_opts {scalar_t__ show_counters; int bcwidth; int pcwidth; scalar_t__ dcnt; } ;
struct cmdline_opts {int use_set; scalar_t__ do_dynamic; } ;
struct TYPE_3__ {scalar_t__ length; } ;
typedef  TYPE_1__ ipfw_obj_tlv ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_state (struct cmdline_opts*,struct format_opts*,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pr_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_format_dyn ; 

__attribute__((used)) static void
prepare_format_opts(struct cmdline_opts *co, struct format_opts *fo,
    ipfw_obj_tlv *rtlv, int rcnt, caddr_t dynbase, size_t dynsz)
{
	int bcwidth, pcwidth, width;
	int n;
	struct ip_fw_bcounter *cntr;
	struct ip_fw_rule *r;

	bcwidth = 0;
	pcwidth = 0;
	if (fo->show_counters != 0) {
		for (n = 0; n < rcnt; n++,
		    rtlv = (ipfw_obj_tlv *)((caddr_t)rtlv + rtlv->length)) {
			cntr = (struct ip_fw_bcounter *)(rtlv + 1);
			r = (struct ip_fw_rule *)((caddr_t)cntr + cntr->size);
			/* skip rules from another set */
			if (co->use_set && r->set != co->use_set - 1)
				continue;

			/* packet counter */
			width = pr_u64(NULL, &cntr->pcnt, 0);
			if (width > pcwidth)
				pcwidth = width;

			/* byte counter */
			width = pr_u64(NULL, &cntr->bcnt, 0);
			if (width > bcwidth)
				bcwidth = width;
		}
	}
	fo->bcwidth = bcwidth;
	fo->pcwidth = pcwidth;

	fo->dcnt = 0;
	if (co->do_dynamic && dynsz > 0)
		foreach_state(co, fo, dynbase, dynsz, prepare_format_dyn, NULL);
}