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
 unsigned int ZU (int) ; 
 int /*<<< orphan*/  assert_u_eq (int /*<<< orphan*/ ,unsigned int,char*,unsigned int) ; 
 int /*<<< orphan*/  assert_zu_ge (size_t,unsigned int,char*,unsigned int,size_t) ; 
 int /*<<< orphan*/  assert_zu_lt (size_t,unsigned int,char*,unsigned int,size_t) ; 

void
assert_lg_floor_range(size_t input, unsigned answer) {
	if (input == 1) {
		assert_u_eq(0, answer, "Got %u as lg_floor of 1", answer);
		return;
	}
	assert_zu_ge(input, (ZU(1) << answer),
	    "Got %u as lg_floor of %zu", answer, input);
	assert_zu_lt(input, (ZU(1) << (answer + 1)),
	    "Got %u as lg_floor of %zu", answer, input);
}