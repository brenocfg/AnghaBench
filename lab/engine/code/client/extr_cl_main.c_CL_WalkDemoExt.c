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
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DEMOEXT ; 
 int /*<<< orphan*/  FS_FOpenFileRead (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_OSPATH ; 
 TYPE_2__* com_legacyprotocol ; 
 TYPE_1__* com_protocol ; 
 scalar_t__* demo_protocols ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static int CL_WalkDemoExt(char *arg, char *name, int *demofile)
{
	int i = 0;
	*demofile = 0;

#ifdef LEGACY_PROTOCOL
	if(com_legacyprotocol->integer > 0)
	{
		Com_sprintf(name, MAX_OSPATH, "demos/%s.%s%d", arg, DEMOEXT, com_legacyprotocol->integer);
		FS_FOpenFileRead(name, demofile, qtrue);
		
		if (*demofile)
		{
			Com_Printf("Demo file: %s\n", name);
			return com_legacyprotocol->integer;
		}
	}
	
	if(com_protocol->integer != com_legacyprotocol->integer)
#endif
	{
		Com_sprintf(name, MAX_OSPATH, "demos/%s.%s%d", arg, DEMOEXT, com_protocol->integer);
		FS_FOpenFileRead(name, demofile, qtrue);

		if (*demofile)
		{
			Com_Printf("Demo file: %s\n", name);
			return com_protocol->integer;
		}
	}

	Com_Printf("Not found: %s\n", name);

	while(demo_protocols[i])
	{
#ifdef LEGACY_PROTOCOL
		if(demo_protocols[i] == com_legacyprotocol->integer)
			continue;
#endif
		if(demo_protocols[i] == com_protocol->integer)
			continue;
	
		Com_sprintf (name, MAX_OSPATH, "demos/%s.%s%d", arg, DEMOEXT, demo_protocols[i]);
		FS_FOpenFileRead( name, demofile, qtrue );
		if (*demofile)
		{
			Com_Printf("Demo file: %s\n", name);

			return demo_protocols[i];
		}
		else
			Com_Printf("Not found: %s\n", name);
		i++;
	}
	
	return -1;
}