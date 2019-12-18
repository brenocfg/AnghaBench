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
struct TYPE_5__ {scalar_t__ bo; size_t jump_to; TYPE_2__* parent; struct TYPE_5__* nextJump; } ;
typedef  TYPE_1__ symbolic_jump_t ;
struct TYPE_6__ {int length; scalar_t__ count; struct TYPE_6__* next; } ;
typedef  TYPE_2__ dest_instruction_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIE (char*) ; 
 scalar_t__ branchAlways ; 
 TYPE_2__** di_pointers ; 
 TYPE_1__* sj_first ; 

__attribute__((used)) static void
PPC_ShrinkJumps( void )
{
	symbolic_jump_t *sj_now = sj_first;
	while ( (sj_now = sj_now->nextJump) ) {
		if ( sj_now->bo == branchAlways )
			// non-conditional branch has 26bit immediate
			sj_now->parent->length = 1;

		else {
			dest_instruction_t *di = di_pointers[ sj_now->jump_to ];
			dest_instruction_t *ji = sj_now->parent;
			long int jump_length = 0;
			if ( ! di )
				DIE( "No instruction to jump to" );
			if ( ji->count > di->count ) {
				do {
					jump_length += di->length;
				} while ( ( di = di->next ) != ji );
			} else {
				jump_length = 1;
				while ( ( ji = ji->next ) != di )
					jump_length += ji->length;
			}
			if ( jump_length < 0x2000 )
				// jump is short, use normal instruction
				sj_now->parent->length = 1;
		}
	}
}