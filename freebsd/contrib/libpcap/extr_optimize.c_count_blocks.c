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
struct icode {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 struct block* JF (struct block*) ; 
 struct block* JT (struct block*) ; 
 int /*<<< orphan*/  Mark (struct icode*,struct block*) ; 
 scalar_t__ isMarked (struct icode*,struct block*) ; 

__attribute__((used)) static int
count_blocks(struct icode *ic, struct block *p)
{
	if (p == 0 || isMarked(ic, p))
		return 0;
	Mark(ic, p);
	return count_blocks(ic, JT(p)) + count_blocks(ic, JF(p)) + 1;
}