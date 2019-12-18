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
struct opcode_obj_rewrite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL3_LOCK () ; 
 int /*<<< orphan*/  CTL3_UNLOCK () ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  compare_opcodes ; 
 struct opcode_obj_rewrite* ctl3_rewriters ; 
 size_t ctl3_rsize ; 
 int /*<<< orphan*/  free (struct opcode_obj_rewrite*,int /*<<< orphan*/ ) ; 
 struct opcode_obj_rewrite* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct opcode_obj_rewrite*,struct opcode_obj_rewrite*,size_t) ; 
 int /*<<< orphan*/  qsort (struct opcode_obj_rewrite*,size_t,int,int /*<<< orphan*/ ) ; 

void
ipfw_add_obj_rewriter(struct opcode_obj_rewrite *rw, size_t count)
{
	size_t sz;
	struct opcode_obj_rewrite *tmp;

	CTL3_LOCK();

	for (;;) {
		sz = ctl3_rsize + count;
		CTL3_UNLOCK();
		tmp = malloc(sizeof(*rw) * sz, M_IPFW, M_WAITOK | M_ZERO);
		CTL3_LOCK();
		if (ctl3_rsize + count <= sz)
			break;

		/* Retry */
		free(tmp, M_IPFW);
	}

	/* Merge old & new arrays */
	sz = ctl3_rsize + count;
	memcpy(tmp, ctl3_rewriters, ctl3_rsize * sizeof(*rw));
	memcpy(&tmp[ctl3_rsize], rw, count * sizeof(*rw));
	qsort(tmp, sz, sizeof(*rw), compare_opcodes);
	/* Switch new and free old */
	if (ctl3_rewriters != NULL)
		free(ctl3_rewriters, M_IPFW);
	ctl3_rewriters = tmp;
	ctl3_rsize = sz;

	CTL3_UNLOCK();
}