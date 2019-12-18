#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int len; int /*<<< orphan*/  vec; } ;
struct TYPE_6__ {TYPE_1__ bt; } ;
typedef  TYPE_2__ prof_gctx_t ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
prof_gctx_comp(const prof_gctx_t *a, const prof_gctx_t *b) {
	unsigned a_len = a->bt.len;
	unsigned b_len = b->bt.len;
	unsigned comp_len = (a_len < b_len) ? a_len : b_len;
	int ret = memcmp(a->bt.vec, b->bt.vec, comp_len * sizeof(void *));
	if (ret == 0) {
		ret = (a_len > b_len) - (a_len < b_len);
	}
	return ret;
}