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
struct branchc {scalar_t__ nbranch; int /*<<< orphan*/  fwd; int /*<<< orphan*/  back; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASTERN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HERE () ; 
 int /*<<< orphan*/  INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCH_ ; 
 int /*<<< orphan*/  OOR1 ; 
 int /*<<< orphan*/  OOR2 ; 
 int /*<<< orphan*/  THERE () ; 

__attribute__((used)) static void
p_branch_ins_offset(struct parse *p, struct branchc *bc)
{

	if (bc->nbranch == 0) {
		INSERT(OCH_, bc->start);	/* offset is wrong */
		bc->fwd = bc->start;
		bc->back = bc->start;
	}

	ASTERN(OOR1, bc->back);
	bc->back = THERE();
	AHEAD(bc->fwd);			/* fix previous offset */
	bc->fwd = HERE();
	EMIT(OOR2, 0);			/* offset is very wrong */
	++bc->nbranch;
}