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
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_2__ {int current; int totallines; short* text; int linewidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM_CompareExtension (char*,char*) ; 
 int /*<<< orphan*/  COM_DefaultExtension (char*,int,char*) ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  FS_FCloseFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_FOpenFileWrite (char*) ; 
 int /*<<< orphan*/  FS_Write (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* Hunk_AllocateTempMemory (int) ; 
 int /*<<< orphan*/  Hunk_FreeTempMemory (char*) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ con ; 
 int /*<<< orphan*/  strlen (char*) ; 

void Con_Dump_f (void)
{
	int		l, x, i;
	short	*line;
	fileHandle_t	f;
	int		bufferlen;
	char	*buffer;
	char	filename[MAX_QPATH];

	if (Cmd_Argc() != 2)
	{
		Com_Printf ("usage: condump <filename>\n");
		return;
	}

	Q_strncpyz( filename, Cmd_Argv( 1 ), sizeof( filename ) );
	COM_DefaultExtension( filename, sizeof( filename ), ".txt" );

	if (!COM_CompareExtension(filename, ".txt"))
	{
		Com_Printf("Con_Dump_f: Only the \".txt\" extension is supported by this command!\n");
		return;
	}

	f = FS_FOpenFileWrite( filename );
	if (!f)
	{
		Com_Printf ("ERROR: couldn't open %s.\n", filename);
		return;
	}

	Com_Printf ("Dumped console text to %s.\n", filename );

	// skip empty lines
	for (l = con.current - con.totallines + 1 ; l <= con.current ; l++)
	{
		line = con.text + (l%con.totallines)*con.linewidth;
		for (x=0 ; x<con.linewidth ; x++)
			if ((line[x] & 0xff) != ' ')
				break;
		if (x != con.linewidth)
			break;
	}

#ifdef _WIN32
	bufferlen = con.linewidth + 3 * sizeof ( char );
#else
	bufferlen = con.linewidth + 2 * sizeof ( char );
#endif

	buffer = Hunk_AllocateTempMemory( bufferlen );

	// write the remaining lines
	buffer[bufferlen-1] = 0;
	for ( ; l <= con.current ; l++)
	{
		line = con.text + (l%con.totallines)*con.linewidth;
		for(i=0; i<con.linewidth; i++)
			buffer[i] = line[i] & 0xff;
		for (x=con.linewidth-1 ; x>=0 ; x--)
		{
			if (buffer[x] == ' ')
				buffer[x] = 0;
			else
				break;
		}
#ifdef _WIN32
		Q_strcat(buffer, bufferlen, "\r\n");
#else
		Q_strcat(buffer, bufferlen, "\n");
#endif
		FS_Write(buffer, strlen(buffer), f);
	}

	Hunk_FreeTempMemory( buffer );
	FS_FCloseFile( f );
}