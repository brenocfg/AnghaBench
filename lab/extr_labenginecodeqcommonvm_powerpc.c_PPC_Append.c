#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long i_count; struct TYPE_5__* next; scalar_t__ count; } ;
typedef  TYPE_1__ dest_instruction_t ;

/* Variables and functions */
 unsigned long FALSE_ICOUNT ; 
 int /*<<< orphan*/  di_count ; 
 TYPE_1__* di_last ; 
 TYPE_1__** di_pointers ; 

__attribute__((used)) static void
PPC_Append(
		dest_instruction_t *di_now,
		unsigned long int i_count
  	  )
{
	di_now->count = di_count++;
	di_now->i_count = i_count;
	di_now->next = NULL;

	di_last->next = di_now;
	di_last = di_now;

	if ( i_count != FALSE_ICOUNT ) {
		if ( ! di_pointers[ i_count ] )
			di_pointers[ i_count ] = di_now;
	}
}