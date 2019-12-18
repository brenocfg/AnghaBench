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
struct fq_codel_si {int /*<<< orphan*/ * flows; } ;
struct dn_sch_inst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DUMMYNET ; 
 TYPE_1__ fq_codel_desc ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fq_codel_free_sched(struct dn_sch_inst *_si)
{
	struct fq_codel_si *si = (struct fq_codel_si *)_si ;

	/* free the flows array */
	free(si->flows , M_DUMMYNET);
	si->flows = NULL;
	fq_codel_desc.ref_count--;

	return 0;
}