#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  writebuf ;
struct TYPE_4__ {int /*<<< orphan*/  subnet; int /*<<< orphan*/  ip; int /*<<< orphan*/  isexception; } ;
typedef  TYPE_1__ serverBan_t ;
typedef  int /*<<< orphan*/  filepath ;
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_5__ {int /*<<< orphan*/ * string; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FS_FCloseFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_GetCurrentGameDir () ; 
 int /*<<< orphan*/  FS_SV_FOpenFileWrite (char*) ; 
 int /*<<< orphan*/  FS_Write (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  NET_AdrToString (int /*<<< orphan*/ ) ; 
 TYPE_1__* serverBans ; 
 int serverBansCount ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_2__* sv_banFile ; 

__attribute__((used)) static void SV_WriteBans(void)
{
	int index;
	fileHandle_t writeto;
	char filepath[MAX_QPATH];
	
	if(!sv_banFile->string || !*sv_banFile->string)
		return;
	
	Com_sprintf(filepath, sizeof(filepath), "%s/%s", FS_GetCurrentGameDir(), sv_banFile->string);

	if((writeto = FS_SV_FOpenFileWrite(filepath)))
	{
		char writebuf[128];
		serverBan_t *curban;
		
		for(index = 0; index < serverBansCount; index++)
		{
			curban = &serverBans[index];
			
			Com_sprintf(writebuf, sizeof(writebuf), "%d %s %d\n",
				    curban->isexception, NET_AdrToString(curban->ip), curban->subnet);
			FS_Write(writebuf, strlen(writebuf), writeto);
		}

		FS_FCloseFile(writeto);
	}
}