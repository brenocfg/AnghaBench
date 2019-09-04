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
struct yyguts_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int yy_init_globals (int /*<<< orphan*/ *) ; 
 scalar_t__ yyalloc (int,int /*<<< orphan*/ *) ; 

int yylex_init(yyscan_t* ptr_yy_globals)
{
    if (ptr_yy_globals == NULL){
        errno = EINVAL;
        return 1;
    }

    *ptr_yy_globals = (yyscan_t) yyalloc ( sizeof( struct yyguts_t ), NULL );

    if (*ptr_yy_globals == NULL){
        errno = ENOMEM;
        return 1;
    }

    /* By setting to 0xAA, we expose bugs in yy_init_globals. Leave at 0x00 for releases. */
    memset(*ptr_yy_globals,0x00,sizeof(struct yyguts_t));

    return yy_init_globals ( *ptr_yy_globals );
}