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
 int /*<<< orphan*/  REG_EMPTY ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
p_branch_empty(struct parse *p, struct branchc *bc)
{

	(void)bc;
	SETERROR(REG_EMPTY);
	return (false);
}