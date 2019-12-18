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
typedef  scalar_t__ yyscan_t ;
struct yyguts_t {int /*<<< orphan*/ * yy_c_buf_p; int /*<<< orphan*/  yy_hold_char; int /*<<< orphan*/ * yytext_ptr; int /*<<< orphan*/  yy_n_chars; } ;
struct TYPE_2__ {int /*<<< orphan*/  yy_input_file; int /*<<< orphan*/ * yy_buf_pos; int /*<<< orphan*/  yy_n_chars; } ;

/* Variables and functions */
 TYPE_1__* YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  yyin ; 

__attribute__((used)) static void yy_load_buffer_state  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
	yyg->yytext_ptr = yyg->yy_c_buf_p = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
	yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
	yyg->yy_hold_char = *yyg->yy_c_buf_p;
}