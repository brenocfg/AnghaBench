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
struct parse {int dummy; } ;
struct branchc {scalar_t__ outer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MORE () ; 
 int p_branch_eat_delim (struct parse*,struct branchc*) ; 
 int /*<<< orphan*/  p_branch_empty (struct parse*,struct branchc*) ; 
 int /*<<< orphan*/  p_branch_ins_offset (struct parse*,struct branchc*) ; 

__attribute__((used)) static bool
p_branch_do(struct parse *p, struct branchc *bc)
{
	int ate = 0;

	ate = p_branch_eat_delim(p, bc);
	if (ate == 0)
		return (false);
	else if ((ate > 1 || (bc->outer && !MORE())) && !p_branch_empty(p, bc))
		/*
		 * Halt parsing only if we have an empty branch and p_branch_empty
		 * indicates that we must not continue. In the future, this will not
		 * necessarily be an error.
		 */
		return (false);
	p_branch_ins_offset(p, bc);

	return (true);
}