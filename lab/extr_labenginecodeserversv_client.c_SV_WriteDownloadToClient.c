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
typedef  int qboolean ;
typedef  int /*<<< orphan*/  pakbuf ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  errorMessage ;
struct TYPE_6__ {int downloadSize; size_t downloadCurrentBlock; size_t downloadClientBlock; size_t downloadXmitBlock; int downloadCount; int* downloadBlockSize; int downloadSendTime; scalar_t__* downloadBlocks; void* downloadEOF; scalar_t__ download; scalar_t__* downloadName; } ;
typedef  TYPE_1__ client_t ;
struct TYPE_9__ {int integer; } ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int time; TYPE_1__* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASEGAME ; 
 int /*<<< orphan*/  BASETA ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Cmd_TokenizeStringIgnoreQuotes (char const*) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,scalar_t__*) ; 
 int DLF_ENABLE ; 
 int DLF_NO_UDP ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 int /*<<< orphan*/  FS_FilenameCompare (int /*<<< orphan*/ ,char*) ; 
 int FS_Read (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 char* FS_ReferencedPakNames () ; 
 int FS_SV_FOpenFileRead (scalar_t__*,scalar_t__*) ; 
 int FS_idPak (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_DOWNLOAD_BLKSIZE ; 
 size_t MAX_DOWNLOAD_WINDOW ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  MSG_WriteByte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_WriteData (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  MSG_WriteLong (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteShort (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NUM_ID_PAKS ; 
 int /*<<< orphan*/  NUM_TA_PAKS ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 scalar_t__ Z_Malloc (int /*<<< orphan*/ ) ; 
 void* qfalse ; 
 void* qtrue ; 
 char* strrchr (char*,char) ; 
 TYPE_4__* sv_allowDownload ; 
 TYPE_3__* sv_pure ; 
 int /*<<< orphan*/  svc_download ; 
 TYPE_2__ svs ; 

int SV_WriteDownloadToClient(client_t *cl, msg_t *msg)
{
	int curindex;
	int unreferenced = 1;
	char errorMessage[1024];
	char pakbuf[MAX_QPATH], *pakptr;
	int numRefPaks;

	if (!*cl->downloadName)
		return 0;	// Nothing being downloaded

	if(!cl->download)
	{
		qboolean idPack = qfalse;
		#ifndef STANDALONE
		qboolean missionPack = qfalse;
		#endif
	
 		// Chop off filename extension.
		Com_sprintf(pakbuf, sizeof(pakbuf), "%s", cl->downloadName);
		pakptr = strrchr(pakbuf, '.');
		
		if(pakptr)
		{
			*pakptr = '\0';

			// Check for pk3 filename extension
			if(!Q_stricmp(pakptr + 1, "pk3"))
			{
				const char *referencedPaks = FS_ReferencedPakNames();

				// Check whether the file appears in the list of referenced
				// paks to prevent downloading of arbitrary files.
				Cmd_TokenizeStringIgnoreQuotes(referencedPaks);
				numRefPaks = Cmd_Argc();

				for(curindex = 0; curindex < numRefPaks; curindex++)
				{
					if(!FS_FilenameCompare(Cmd_Argv(curindex), pakbuf))
					{
						unreferenced = 0;

						// now that we know the file is referenced,
						// check whether it's legal to download it.
#ifndef STANDALONE
						missionPack = FS_idPak(pakbuf, BASETA, NUM_TA_PAKS);
						idPack = missionPack;
#endif
						idPack = idPack || FS_idPak(pakbuf, BASEGAME, NUM_ID_PAKS);

						break;
					}
				}
			}
		}

		cl->download = 0;

		// We open the file here
		if ( !(sv_allowDownload->integer & DLF_ENABLE) ||
			(sv_allowDownload->integer & DLF_NO_UDP) ||
			idPack || unreferenced ||
			( cl->downloadSize = FS_SV_FOpenFileRead( cl->downloadName, &cl->download ) ) < 0 ) {
			// cannot auto-download file
			if(unreferenced)
			{
				Com_Printf("clientDownload: %d : \"%s\" is not referenced and cannot be downloaded.\n", (int) (cl - svs.clients), cl->downloadName);
				Com_sprintf(errorMessage, sizeof(errorMessage), "File \"%s\" is not referenced and cannot be downloaded.", cl->downloadName);
			}
			else if (idPack) {
				Com_Printf("clientDownload: %d : \"%s\" cannot download id pk3 files\n", (int) (cl - svs.clients), cl->downloadName);
#ifndef STANDALONE
				if(missionPack)
				{
					Com_sprintf(errorMessage, sizeof(errorMessage), "Cannot autodownload Team Arena file \"%s\"\n"
									"The Team Arena mission pack can be found in your local game store.", cl->downloadName);
				}
				else
#endif
				{
					Com_sprintf(errorMessage, sizeof(errorMessage), "Cannot autodownload id pk3 file \"%s\"", cl->downloadName);
				}
			}
			else if ( !(sv_allowDownload->integer & DLF_ENABLE) ||
				(sv_allowDownload->integer & DLF_NO_UDP) ) {

				Com_Printf("clientDownload: %d : \"%s\" download disabled\n", (int) (cl - svs.clients), cl->downloadName);
				if (sv_pure->integer) {
					Com_sprintf(errorMessage, sizeof(errorMessage), "Could not download \"%s\" because autodownloading is disabled on the server.\n\n"
										"You will need to get this file elsewhere before you "
										"can connect to this pure server.\n", cl->downloadName);
				} else {
					Com_sprintf(errorMessage, sizeof(errorMessage), "Could not download \"%s\" because autodownloading is disabled on the server.\n\n"
                    "The server you are connecting to is not a pure server, "
                    "set autodownload to No in your settings and you might be "
                    "able to join the game anyway.\n", cl->downloadName);
				}
			} else {
        // NOTE TTimo this is NOT supposed to happen unless bug in our filesystem scheme?
        //   if the pk3 is referenced, it must have been found somewhere in the filesystem
				Com_Printf("clientDownload: %d : \"%s\" file not found on server\n", (int) (cl - svs.clients), cl->downloadName);
				Com_sprintf(errorMessage, sizeof(errorMessage), "File \"%s\" not found on server for autodownloading.\n", cl->downloadName);
			}
			MSG_WriteByte( msg, svc_download );
			MSG_WriteShort( msg, 0 ); // client is expecting block zero
			MSG_WriteLong( msg, -1 ); // illegal file size
			MSG_WriteString( msg, errorMessage );

			*cl->downloadName = 0;
			
			if(cl->download)
				FS_FCloseFile(cl->download);
			
			return 1;
		}
 
		Com_Printf( "clientDownload: %d : beginning \"%s\"\n", (int) (cl - svs.clients), cl->downloadName );
		
		// Init
		cl->downloadCurrentBlock = cl->downloadClientBlock = cl->downloadXmitBlock = 0;
		cl->downloadCount = 0;
		cl->downloadEOF = qfalse;
	}

	// Perform any reads that we need to
	while (cl->downloadCurrentBlock - cl->downloadClientBlock < MAX_DOWNLOAD_WINDOW &&
		cl->downloadSize != cl->downloadCount) {

		curindex = (cl->downloadCurrentBlock % MAX_DOWNLOAD_WINDOW);

		if (!cl->downloadBlocks[curindex])
			cl->downloadBlocks[curindex] = Z_Malloc(MAX_DOWNLOAD_BLKSIZE);

		cl->downloadBlockSize[curindex] = FS_Read( cl->downloadBlocks[curindex], MAX_DOWNLOAD_BLKSIZE, cl->download );

		if (cl->downloadBlockSize[curindex] < 0) {
			// EOF right now
			cl->downloadCount = cl->downloadSize;
			break;
		}

		cl->downloadCount += cl->downloadBlockSize[curindex];

		// Load in next block
		cl->downloadCurrentBlock++;
	}

	// Check to see if we have eof condition and add the EOF block
	if (cl->downloadCount == cl->downloadSize &&
		!cl->downloadEOF &&
		cl->downloadCurrentBlock - cl->downloadClientBlock < MAX_DOWNLOAD_WINDOW) {

		cl->downloadBlockSize[cl->downloadCurrentBlock % MAX_DOWNLOAD_WINDOW] = 0;
		cl->downloadCurrentBlock++;

		cl->downloadEOF = qtrue;  // We have added the EOF block
	}

	if (cl->downloadClientBlock == cl->downloadCurrentBlock)
		return 0; // Nothing to transmit

	// Write out the next section of the file, if we have already reached our window,
	// automatically start retransmitting
	if (cl->downloadXmitBlock == cl->downloadCurrentBlock)
	{
		// We have transmitted the complete window, should we start resending?
		if (svs.time - cl->downloadSendTime > 1000)
			cl->downloadXmitBlock = cl->downloadClientBlock;
		else
			return 0;
	}

	// Send current block
	curindex = (cl->downloadXmitBlock % MAX_DOWNLOAD_WINDOW);

	MSG_WriteByte( msg, svc_download );
	MSG_WriteShort( msg, cl->downloadXmitBlock );

	// block zero is special, contains file size
	if ( cl->downloadXmitBlock == 0 )
		MSG_WriteLong( msg, cl->downloadSize );

	MSG_WriteShort( msg, cl->downloadBlockSize[curindex] );

	// Write the block
	if(cl->downloadBlockSize[curindex])
		MSG_WriteData(msg, cl->downloadBlocks[curindex], cl->downloadBlockSize[curindex]);

	Com_DPrintf( "clientDownload: %d : writing block %d\n", (int) (cl - svs.clients), cl->downloadXmitBlock );

	// Move on to the next block
	// It will get sent with next snap shot.  The rate will keep us in line.
	cl->downloadXmitBlock++;
	cl->downloadSendTime = svs.time;

	return 1;
}