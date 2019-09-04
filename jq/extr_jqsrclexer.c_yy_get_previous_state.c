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
typedef  size_t yy_state_type ;
struct yyguts_t {size_t yy_start; char* yytext_ptr; char* yy_c_buf_p; size_t yy_last_accepting_state; char* yy_last_accepting_cpos; } ;
typedef  size_t YY_CHAR ;

/* Variables and functions */
 int YY_MORE_ADJ ; 
 size_t YY_SC_TO_UI (char) ; 
 scalar_t__* yy_accept ; 
 size_t* yy_base ; 
 size_t* yy_chk ; 
 scalar_t__* yy_def ; 
 int* yy_ec ; 
 size_t* yy_meta ; 
 size_t* yy_nxt ; 

__attribute__((used)) static yy_state_type yy_get_previous_state (yyscan_t yyscanner)
{
	yy_state_type yy_current_state;
	char *yy_cp;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	yy_current_state = yyg->yy_start;

	for ( yy_cp = yyg->yytext_ptr + YY_MORE_ADJ; yy_cp < yyg->yy_c_buf_p; ++yy_cp )
		{
		YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
		if ( yy_accept[yy_current_state] )
			{
			yyg->yy_last_accepting_state = yy_current_state;
			yyg->yy_last_accepting_cpos = yy_cp;
			}
		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
			{
			yy_current_state = (int) yy_def[yy_current_state];
			if ( yy_current_state >= 157 )
				yy_c = yy_meta[yy_c];
			}
		yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
		}

	return yy_current_state;
}