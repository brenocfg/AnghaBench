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

/* Variables and functions */
 unsigned int BT_COUNT_CHECK_INTERVAL ; 
 unsigned int DUMP_INTERVAL ; 
 unsigned int NALLOCS_PER_THREAD ; 
 void* alloc_from_permuted_backtrace (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert_zu_le (size_t,size_t,char*) ; 
 int /*<<< orphan*/  dallocx (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mallctl (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t prof_bt_count () ; 

__attribute__((used)) static void *
thd_start(void *varg) {
	unsigned thd_ind = *(unsigned *)varg;
	size_t bt_count_prev, bt_count;
	unsigned i_prev, i;

	i_prev = 0;
	bt_count_prev = 0;
	for (i = 0; i < NALLOCS_PER_THREAD; i++) {
		void *p = alloc_from_permuted_backtrace(thd_ind, i);
		dallocx(p, 0);
		if (i % DUMP_INTERVAL == 0) {
			assert_d_eq(mallctl("prof.dump", NULL, NULL, NULL, 0),
			    0, "Unexpected error while dumping heap profile");
		}

		if (i % BT_COUNT_CHECK_INTERVAL == 0 ||
		    i+1 == NALLOCS_PER_THREAD) {
			bt_count = prof_bt_count();
			assert_zu_le(bt_count_prev+(i-i_prev), bt_count,
			    "Expected larger backtrace count increase");
			i_prev = i;
			bt_count_prev = bt_count;
		}
	}

	return NULL;
}