#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  st_next; scalar_t__ force_eof; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _drop_stack_do (int /*<<< orphan*/ ) ; 
 TYPE_1__* lex_stack ; 

int/*BOOL*/
lex_flush_stack()
{
	int retv = FALSE;

	if (NULL != lex_stack) {
		retv = !lex_stack->force_eof;
		lex_stack->force_eof = TRUE;
		lex_stack->st_next = _drop_stack_do(
					lex_stack->st_next);
	}
	return retv;
}