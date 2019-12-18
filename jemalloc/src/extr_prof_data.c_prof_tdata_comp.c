#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ thr_uid; scalar_t__ thr_discrim; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */

__attribute__((used)) static int
prof_tdata_comp(const prof_tdata_t *a, const prof_tdata_t *b) {
	int ret;
	uint64_t a_uid = a->thr_uid;
	uint64_t b_uid = b->thr_uid;

	ret = ((a_uid > b_uid) - (a_uid < b_uid));
	if (ret == 0) {
		uint64_t a_discrim = a->thr_discrim;
		uint64_t b_discrim = b->thr_discrim;

		ret = ((a_discrim > b_discrim) - (a_discrim < b_discrim));
	}
	return ret;
}