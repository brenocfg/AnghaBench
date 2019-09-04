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
typedef  scalar_t__ yyscan_t ;
struct yyguts_t {scalar_t__ yy_start_stack_ptr; int /*<<< orphan*/ * yy_start_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YY_FATAL_ERROR (char*) ; 

__attribute__((used)) static void yy_pop_state  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	if ( --yyg->yy_start_stack_ptr < 0 )
		YY_FATAL_ERROR( "start-condition stack underflow" );

	BEGIN(yyg->yy_start_stack[yyg->yy_start_stack_ptr]);
}