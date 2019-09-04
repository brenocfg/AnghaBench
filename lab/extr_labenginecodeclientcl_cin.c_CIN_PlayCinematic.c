#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  cinematics_t ;
struct TYPE_9__ {size_t currentHandle; scalar_t__* file; } ;
struct TYPE_8__ {scalar_t__ ROQSize; int holdAtEnd; int alterGameState; int playonwalls; int silent; int shader; int /*<<< orphan*/  status; int /*<<< orphan*/  iFile; int /*<<< orphan*/  CIN_WIDTH; int /*<<< orphan*/  CIN_HEIGHT; scalar_t__* fileName; } ;
struct TYPE_7__ {int integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_CINEMATIC ; 
 size_t CIN_HandleForVideo () ; 
 int /*<<< orphan*/  CIN_SetExtents (size_t,int,int,int,int) ; 
 int /*<<< orphan*/  CIN_SetLooping (size_t,int) ; 
 int CIN_hold ; 
 int CIN_loop ; 
 int CIN_shader ; 
 int CIN_silent ; 
 int CIN_system ; 
 int /*<<< orphan*/  Com_DPrintf (char*,...) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  Con_Close () ; 
 int /*<<< orphan*/  DEFAULT_CIN_HEIGHT ; 
 int /*<<< orphan*/  DEFAULT_CIN_WIDTH ; 
 int /*<<< orphan*/  FMV_PLAY ; 
 scalar_t__ FS_FOpenFileRead (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_Read (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int MAX_OSPATH ; 
 int MAX_VIDEO_HANDLES ; 
 int /*<<< orphan*/  RoQShutdown () ; 
 int /*<<< orphan*/  RoQ_init () ; 
 int /*<<< orphan*/  UIMENU_NONE ; 
 int /*<<< orphan*/  UI_SET_ACTIVE_MENU ; 
 int /*<<< orphan*/  VM_Call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ cin ; 
 TYPE_3__* cinTable ; 
 TYPE_2__* cl_inGameVideo ; 
 TYPE_1__ clc ; 
 size_t currentHandle ; 
 int /*<<< orphan*/  initRoQ () ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/ * s_rawend ; 
 int /*<<< orphan*/  s_soundtime ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 scalar_t__ uivm ; 

int CIN_PlayCinematic( const char *arg, int x, int y, int w, int h, int systemBits ) {
	unsigned short RoQID;
	char	name[MAX_OSPATH];
	int		i;

	if (strstr(arg, "/") == NULL && strstr(arg, "\\") == NULL) {
		Com_sprintf (name, sizeof(name), "video/%s", arg);
	} else {
		Com_sprintf (name, sizeof(name), "%s", arg);
	}

	if (!(systemBits & CIN_system)) {
		for ( i = 0 ; i < MAX_VIDEO_HANDLES ; i++ ) {
			if (!strcmp(cinTable[i].fileName, name) ) {
				return i;
			}
		}
	}

	Com_DPrintf("CIN_PlayCinematic( %s )\n", arg);

	Com_Memset(&cin, 0, sizeof(cinematics_t) );
	currentHandle = CIN_HandleForVideo();

	cin.currentHandle = currentHandle;

	strcpy(cinTable[currentHandle].fileName, name);

	cinTable[currentHandle].ROQSize = 0;
	cinTable[currentHandle].ROQSize = FS_FOpenFileRead (cinTable[currentHandle].fileName, &cinTable[currentHandle].iFile, qtrue);

	if (cinTable[currentHandle].ROQSize<=0) {
		Com_DPrintf("play(%s), ROQSize<=0\n", arg);
		cinTable[currentHandle].fileName[0] = 0;
		return -1;
	}

	CIN_SetExtents(currentHandle, x, y, w, h);
	CIN_SetLooping(currentHandle, (systemBits & CIN_loop)!=0);

	cinTable[currentHandle].CIN_HEIGHT = DEFAULT_CIN_HEIGHT;
	cinTable[currentHandle].CIN_WIDTH  =  DEFAULT_CIN_WIDTH;
	cinTable[currentHandle].holdAtEnd = (systemBits & CIN_hold) != 0;
	cinTable[currentHandle].alterGameState = (systemBits & CIN_system) != 0;
	cinTable[currentHandle].playonwalls = 1;
	cinTable[currentHandle].silent = (systemBits & CIN_silent) != 0;
	cinTable[currentHandle].shader = (systemBits & CIN_shader) != 0;

	if (cinTable[currentHandle].alterGameState) {
		// close the menu
		if ( uivm ) {
			VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_NONE );
		}
	} else {
		cinTable[currentHandle].playonwalls = cl_inGameVideo->integer;
	}

	initRoQ();
					
	FS_Read (cin.file, 16, cinTable[currentHandle].iFile);

	RoQID = (unsigned short)(cin.file[0]) + (unsigned short)(cin.file[1])*256;
	if (RoQID == 0x1084)
	{
		RoQ_init();
//		FS_Read (cin.file, cinTable[currentHandle].RoQFrameSize+8, cinTable[currentHandle].iFile);

		cinTable[currentHandle].status = FMV_PLAY;
		Com_DPrintf("trFMV::play(), playing %s\n", arg);

		if (cinTable[currentHandle].alterGameState) {
			clc.state = CA_CINEMATIC;
		}
		
		Con_Close();

		if (!cinTable[currentHandle].silent) {
			s_rawend[0] = s_soundtime;
		}

		return currentHandle;
	}
	Com_DPrintf("trFMV::play(), invalid RoQ ID\n");

	RoQShutdown();
	return -1;
}