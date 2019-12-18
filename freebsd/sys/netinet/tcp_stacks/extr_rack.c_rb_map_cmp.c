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
struct rack_sendmap {int /*<<< orphan*/  r_end; int /*<<< orphan*/  r_start; } ;

/* Variables and functions */
 scalar_t__ SEQ_GEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
rb_map_cmp(struct rack_sendmap *b, struct rack_sendmap *a)
{
	if (SEQ_GEQ(b->r_start, a->r_start) &&
	    SEQ_LT(b->r_start, a->r_end)) {
		/* 
		 * The entry b is within the
		 * block a. i.e.:
		 * a --   |-------------|
		 * b --   |----|
		 * <or>
		 * b --       |------|
		 * <or>
		 * b --       |-----------|
		 */
		return (0);
	} else if (SEQ_GEQ(b->r_start, a->r_end)) {
		/* 
		 * b falls as either the next
		 * sequence block after a so a
		 * is said to be smaller than b.
		 * i.e:
		 * a --   |------|
		 * b --          |--------|
		 * or 
		 * b --              |-----|     
		 */
		return (1);
	}
	/*
	 * Whats left is where a is
	 * larger than b. i.e:
	 * a --         |-------|
	 * b --  |---|
	 * or even possibly
	 * b --   |--------------|
	 */
	return (-1);
}