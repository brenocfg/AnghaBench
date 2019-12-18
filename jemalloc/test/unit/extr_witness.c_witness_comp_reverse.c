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
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  rank; } ;
typedef  TYPE_1__ witness_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_u_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
witness_comp_reverse(const witness_t *a, void *oa, const witness_t *b,
    void *ob) {
	assert_u_eq(a->rank, b->rank, "Witnesses should have equal rank");

	assert(oa == (void *)a);
	assert(ob == (void *)b);

	return -strcmp(a->name, b->name);
}