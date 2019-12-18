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
typedef  struct yyguts_t* yyscan_t ;
struct yyguts_t {int dummy; } ;
typedef  int /*<<< orphan*/  YY_EXTRA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct yyguts_t*,int,int) ; 
 int yy_init_globals (struct yyguts_t*) ; 
 scalar_t__ yyalloc (int,struct yyguts_t*) ; 
 int /*<<< orphan*/  yyset_extra (int /*<<< orphan*/ ,struct yyguts_t*) ; 

int yylex_init_extra( YY_EXTRA_TYPE yy_user_defined, yyscan_t* ptr_yy_globals )
{
    struct yyguts_t dummy_yyguts;

    yyset_extra (yy_user_defined, &dummy_yyguts);

    if (ptr_yy_globals == NULL){
        errno = EINVAL;
        return 1;
    }

    *ptr_yy_globals = (yyscan_t) yyalloc ( sizeof( struct yyguts_t ), &dummy_yyguts );

    if (*ptr_yy_globals == NULL){
        errno = ENOMEM;
        return 1;
    }

    /* By setting to 0xAA, we expose bugs in
    yy_init_globals. Leave at 0x00 for releases. */
    memset(*ptr_yy_globals,0x00,sizeof(struct yyguts_t));

    yyset_extra (yy_user_defined, *ptr_yy_globals);

    return yy_init_globals ( *ptr_yy_globals );
}