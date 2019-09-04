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
typedef  int /*<<< orphan*/ * yyscan_t ;
struct yyguts_t {int /*<<< orphan*/ * yy_start_stack; int /*<<< orphan*/ * yy_buffer_stack; } ;

/* Variables and functions */
 scalar_t__ YY_CURRENT_BUFFER ; 
 int /*<<< orphan*/ * YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  yy_delete_buffer (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yy_init_globals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yypop_buffer_state (int /*<<< orphan*/ *) ; 

int yylex_destroy  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

    /* Pop the buffer stack, destroying each element. */
	while(YY_CURRENT_BUFFER){
		yy_delete_buffer( YY_CURRENT_BUFFER , yyscanner );
		YY_CURRENT_BUFFER_LVALUE = NULL;
		yypop_buffer_state(yyscanner);
	}

	/* Destroy the stack itself. */
	yyfree(yyg->yy_buffer_stack , yyscanner);
	yyg->yy_buffer_stack = NULL;

    /* Destroy the start condition stack. */
        yyfree( yyg->yy_start_stack , yyscanner );
        yyg->yy_start_stack = NULL;

    /* Reset the globals. This is important in a non-reentrant scanner so the next time
     * yylex() is called, initialization will occur. */
    yy_init_globals( yyscanner);

    /* Destroy the main struct (reentrant only). */
    yyfree ( yyscanner , yyscanner );
    yyscanner = NULL;
    return 0;
}