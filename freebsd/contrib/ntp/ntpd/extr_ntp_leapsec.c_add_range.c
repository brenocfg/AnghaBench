#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; scalar_t__ base_tai; } ;
struct TYPE_10__ {TYPE_1__ head; TYPE_3__* info; } ;
typedef  TYPE_2__ leap_table_t ;
struct TYPE_11__ {scalar_t__ taiof; } ;
typedef  TYPE_3__ leap_info_t ;

/* Variables and functions */
 size_t MAX_HIST ; 
 int TRUE ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  reset_times (TYPE_2__*) ; 

__attribute__((used)) static int/*BOOL*/
add_range(
	leap_table_t *      pt,
	const leap_info_t * pi)
{
	/* If the table is full, make room by throwing out the oldest
	 * entry. But remember the accumulated leap seconds!
	 *
	 * Setting the first entry is a bit tricky, too: Simply assuming
	 * it is an insertion is wrong if the first entry is a dynamic
	 * leap second removal. So we decide on the sign -- if the first
	 * entry has a negative offset, we assume that it is a leap
	 * second removal. In both cases the table base offset is set
	 * accordingly to reflect the decision.
	 *
	 * In practice starting with a removal can only happen if the
	 * first entry is a dynamic request without having a leap file
	 * for the history proper.
	 */
	if (pt->head.size == 0) {
		if (pi->taiof >= 0)
			pt->head.base_tai = pi->taiof - 1;
		else
			pt->head.base_tai = pi->taiof + 1;
	} else if (pt->head.size >= MAX_HIST) {
		pt->head.size     = MAX_HIST - 1;
		pt->head.base_tai = pt->info[pt->head.size].taiof;
	}

	/* make room in lower end and insert item */
	memmove(pt->info+1, pt->info, pt->head.size*sizeof(*pt->info));
	pt->info[0] = *pi;
	pt->head.size++;

	/* invalidate the cached limit data -- we might have news ;-)
	 *
	 * This blocks a spurious transition detection. OTOH, if you add
	 * a value after the last query before a leap transition was
	 * expected to occur, this transition trigger is lost. But we
	 * can probably live with that.
	 */
	reset_times(pt);
	return TRUE;
}