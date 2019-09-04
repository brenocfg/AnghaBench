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
struct yyguts_t {int dummy; } ;
typedef  int /*<<< orphan*/  YYLTYPE ;

/* Variables and functions */
 int /*<<< orphan*/ * yylloc ; 

void yyset_lloc (YYLTYPE *  yylloc_param , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    yylloc = yylloc_param;
}