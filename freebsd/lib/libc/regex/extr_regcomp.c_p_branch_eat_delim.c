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
struct branchc {int dummy; } ;

/* Variables and functions */
 scalar_t__ EAT (char) ; 

__attribute__((used)) static int
p_branch_eat_delim(struct parse *p, struct branchc *bc)
{
	int nskip;

	(void)bc;
	nskip = 0;
	while (EAT('|'))
		++nskip;
	return (nskip);
}