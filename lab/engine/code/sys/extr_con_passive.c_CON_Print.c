#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ integer; } ;
struct TYPE_3__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Sys_AnsiColorPrint (char const*) ; 
 TYPE_2__* com_ansiColor ; 
 TYPE_1__* com_logToStdErr ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void CON_Print( const char *msg )
{
	if (com_logToStdErr && com_logToStdErr->integer ) {
		if( com_ansiColor && com_ansiColor->integer ) {
			Sys_AnsiColorPrint( msg );
		} else {
			fputs( msg, stderr );
		}
	}
}