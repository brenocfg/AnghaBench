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
struct buf_pr {int dummy; } ;
struct TYPE_3__ {char const* qid; } ;
typedef  TYPE_1__ ipfw_insn_altq ;

/* Variables and functions */
 char* altq_qid_to_name (char const*) ; 
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,char const*) ; 

void
print_altq_cmd(struct buf_pr *bp, ipfw_insn_altq *altqptr)
{
	if (altqptr) {
		const char *qname;

		qname = altq_qid_to_name(altqptr->qid);
		if (qname == NULL)
			bprintf(bp, " altq ?<%u>", altqptr->qid);
		else
			bprintf(bp, " altq %s", qname);
	}
}