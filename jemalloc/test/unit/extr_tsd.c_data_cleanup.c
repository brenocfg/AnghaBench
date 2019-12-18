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
#define  MALLOC_TSD_TEST_DATA_INIT 128 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_x_eq (int,int,char*) ; 
 int /*<<< orphan*/  dallocx (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ data_cleanup_count ; 
 void* mallocx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  not_reached () ; 

void
data_cleanup(int *data) {
	if (data_cleanup_count == 0) {
		assert_x_eq(*data, MALLOC_TSD_TEST_DATA_INIT,
		    "Argument passed into cleanup function should match tsd "
		    "value");
	}
	++data_cleanup_count;

	/*
	 * Allocate during cleanup for two rounds, in order to assure that
	 * jemalloc's internal tsd reinitialization happens.
	 */
	bool reincarnate = false;
	switch (*data) {
	case MALLOC_TSD_TEST_DATA_INIT:
		*data = 1;
		reincarnate = true;
		break;
	case 1:
		*data = 2;
		reincarnate = true;
		break;
	case 2:
		return;
	default:
		not_reached();
	}

	if (reincarnate) {
		void *p = mallocx(1, 0);
		assert_ptr_not_null(p, "Unexpeced mallocx() failure");
		dallocx(p, 0);
	}
}