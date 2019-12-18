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
struct TYPE_5__ {unsigned long jump_to; long bo; long bi; unsigned long ext; struct TYPE_5__* nextJump; TYPE_2__* parent; } ;
typedef  TYPE_1__ symbolic_jump_t ;
struct TYPE_6__ {int length; TYPE_1__* jump; } ;
typedef  TYPE_2__ dest_instruction_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_Append (TYPE_2__*,unsigned long) ; 
 void* PPC_Malloc (int) ; 
 long branchAlways ; 
 TYPE_1__* sj_last ; 

__attribute__((used)) static void
PPC_PrepareJump(
		unsigned long int i_count,
		unsigned long int dest,
		long int bo,
		long int bi,
		unsigned long int ext
	)
{
	dest_instruction_t *di_now = PPC_Malloc( sizeof( dest_instruction_t ) );
	symbolic_jump_t *sj = PPC_Malloc( sizeof( symbolic_jump_t ) );

	sj->jump_to = dest;
	sj->bo = bo;
	sj->bi = bi;
	sj->ext = ext;
	sj->parent = di_now;
	sj->nextJump = NULL;

	sj_last->nextJump = sj;
	sj_last = sj;

	di_now->length = (bo == branchAlways ? 1 : 2);
	di_now->jump = sj;

	PPC_Append( di_now, i_count );
}