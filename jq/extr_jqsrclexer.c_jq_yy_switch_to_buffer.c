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
typedef  scalar_t__ yyscan_t ;
struct yyguts_t {int yy_did_buffer_switch_on_eof; int /*<<< orphan*/  yy_n_chars; int /*<<< orphan*/ * yy_c_buf_p; int /*<<< orphan*/  yy_hold_char; } ;
typedef  TYPE_1__* YY_BUFFER_STATE ;
struct TYPE_5__ {int /*<<< orphan*/  yy_n_chars; int /*<<< orphan*/ * yy_buf_pos; } ;

/* Variables and functions */
 TYPE_1__* YY_CURRENT_BUFFER ; 
 TYPE_1__* YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  yy_load_buffer_state (scalar_t__) ; 
 int /*<<< orphan*/  yyensure_buffer_stack (scalar_t__) ; 

void yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	/* TODO. We should be able to replace this entire function body
	 * with
	 *		yypop_buffer_state();
	 *		yypush_buffer_state(new_buffer);
     */
	yyensure_buffer_stack (yyscanner);
	if ( YY_CURRENT_BUFFER == new_buffer )
		return;

	if ( YY_CURRENT_BUFFER )
		{
		/* Flush out information for old buffer. */
		*yyg->yy_c_buf_p = yyg->yy_hold_char;
		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
		}

	YY_CURRENT_BUFFER_LVALUE = new_buffer;
	yy_load_buffer_state( yyscanner );

	/* We don't actually know whether we did this switch during
	 * EOF (yywrap()) processing, but the only time this flag
	 * is looked at is after yywrap() is called, so it's safe
	 * to go ahead and always set it.
	 */
	yyg->yy_did_buffer_switch_on_eof = 1;
}