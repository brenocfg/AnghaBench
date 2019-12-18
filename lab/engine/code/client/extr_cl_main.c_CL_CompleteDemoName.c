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
typedef  int /*<<< orphan*/  demoExt ;
struct TYPE_2__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEMOEXT ; 
 int /*<<< orphan*/  Field_CompleteFilename (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* com_protocol ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void CL_CompleteDemoName( char *args, int argNum )
{
	if( argNum == 2 )
	{
		char demoExt[ 16 ];

		Com_sprintf(demoExt, sizeof(demoExt), ".%s%d", DEMOEXT, com_protocol->integer);
		Field_CompleteFilename( "demos", demoExt, qtrue, qtrue );
	}
}