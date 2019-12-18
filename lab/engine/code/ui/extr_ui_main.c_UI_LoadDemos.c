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
struct TYPE_2__ {int demoCount; int /*<<< orphan*/ * demoList; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_LEN (char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEMOEXT ; 
 int MAX_DEMOS ; 
 int NAMEBUFSIZE ; 
 int /*<<< orphan*/  String_Alloc (char*) ; 
 int strlen (char*) ; 
 int trap_Cvar_VariableValue (char*) ; 
 int trap_FS_GetFileList (char*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ uiInfo ; 

__attribute__((used)) static void UI_LoadDemos( void ) {
	char	demolist[NAMEBUFSIZE];
	char	demoExt[32];
	char	*demoname;
	int	i, j, len;
	int	protocol, protocolLegacy;

	protocolLegacy = trap_Cvar_VariableValue("com_legacyprotocol");
	protocol = trap_Cvar_VariableValue("com_protocol");

	if(!protocol)
		protocol = trap_Cvar_VariableValue("protocol");
	if(protocolLegacy == protocol)
		protocolLegacy = 0;

	Com_sprintf(demoExt, sizeof(demoExt), ".%s%d", DEMOEXT, protocol);
	uiInfo.demoCount = trap_FS_GetFileList("demos", demoExt, demolist, ARRAY_LEN(demolist));
	
	demoname = demolist;
	i = 0;

	for(j = 0; j < 2; j++)
	{
		if(uiInfo.demoCount > MAX_DEMOS)
			uiInfo.demoCount = MAX_DEMOS;

		for(; i < uiInfo.demoCount; i++)
		{
			len = strlen(demoname);
			uiInfo.demoList[i] = String_Alloc(demoname);
			demoname += len + 1;
		}
		
		if(!j)
		{
		        if(protocolLegacy > 0 && uiInfo.demoCount < MAX_DEMOS)
		        {
                        	Com_sprintf(demoExt, sizeof(demoExt), ".%s%d", DEMOEXT, protocolLegacy);
                        	uiInfo.demoCount += trap_FS_GetFileList("demos", demoExt, demolist, ARRAY_LEN(demolist));
                        	demoname = demolist;
                        }
                        else
                                break;
		}
	}

}