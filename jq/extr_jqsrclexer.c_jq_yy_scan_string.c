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
typedef  int /*<<< orphan*/  yyscan_t ;
typedef  int /*<<< orphan*/  YY_BUFFER_STATE ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  yy_scan_bytes (char const*,int,int /*<<< orphan*/ ) ; 

YY_BUFFER_STATE yy_scan_string (const char * yystr , yyscan_t yyscanner)
{
    
	return yy_scan_bytes( yystr, (int) strlen(yystr) , yyscanner);
}