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
struct TYPE_2__ {int all_filters_applied; scalar_t__ write_ptr; scalar_t__ last_write_ptr; int /*<<< orphan*/  filters; } ;
struct rar5 {TYPE_1__ cstate; } ;
struct filter_info {scalar_t__ block_start; scalar_t__ block_length; } ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_RETRY ; 
 scalar_t__ CDE_OK ; 
 int /*<<< orphan*/  cdeque_filter_p (struct filter_info**) ; 
 scalar_t__ cdeque_front (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdeque_pop_front (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct filter_info*) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int /*<<< orphan*/  push_window_data (struct archive_read*,struct rar5*,scalar_t__,scalar_t__) ; 
 int run_filter (struct archive_read*,struct filter_info*) ; 

__attribute__((used)) static int apply_filters(struct archive_read* a) {
	struct filter_info* flt;
	struct rar5* rar = get_context(a);
	int ret;

	rar->cstate.all_filters_applied = 0;

	/* Get the first filter that can be applied to our data. The data
	 * needs to be fully unpacked before the filter can be run. */
	if(CDE_OK == cdeque_front(&rar->cstate.filters,
	    cdeque_filter_p(&flt))) {
		/* Check if our unpacked data fully covers this filter's
		 * range. */
		if(rar->cstate.write_ptr > flt->block_start &&
		    rar->cstate.write_ptr >= flt->block_start +
		    flt->block_length) {
			/* Check if we have some data pending to be written
			 * right before the filter's start offset. */
			if(rar->cstate.last_write_ptr == flt->block_start) {
				/* Run the filter specified by descriptor
				 * `flt`. */
				ret = run_filter(a, flt);
				if(ret != ARCHIVE_OK) {
					/* Filter failure, return error. */
					return ret;
				}

				/* Filter descriptor won't be needed anymore
				 * after it's used, * so remove it from the
				 * filter list and free its memory. */
				(void) cdeque_pop_front(&rar->cstate.filters,
				    cdeque_filter_p(&flt));

				free(flt);
			} else {
				/* We can't run filters yet, dump the memory
				 * right before the filter. */
				push_window_data(a, rar,
				    rar->cstate.last_write_ptr,
				    flt->block_start);
			}

			/* Return 'filter applied or not needed' state to the
			 * caller. */
			return ARCHIVE_RETRY;
		}
	}

	rar->cstate.all_filters_applied = 1;
	return ARCHIVE_OK;
}