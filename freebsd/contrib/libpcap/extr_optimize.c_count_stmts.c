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
typedef  scalar_t__ u_int ;
struct icode {int dummy; } ;
struct block {scalar_t__ longjf; scalar_t__ longjt; int /*<<< orphan*/  stmts; } ;

/* Variables and functions */
 struct block* JF (struct block*) ; 
 struct block* JT (struct block*) ; 
 int /*<<< orphan*/  Mark (struct icode*,struct block*) ; 
 scalar_t__ isMarked (struct icode*,struct block*) ; 
 scalar_t__ slength (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
count_stmts(struct icode *ic, struct block *p)
{
	u_int n;

	if (p == 0 || isMarked(ic, p))
		return 0;
	Mark(ic, p);
	n = count_stmts(ic, JT(p)) + count_stmts(ic, JF(p));
	return slength(p->stmts) + n + 1 + p->longjt + p->longjf;
}