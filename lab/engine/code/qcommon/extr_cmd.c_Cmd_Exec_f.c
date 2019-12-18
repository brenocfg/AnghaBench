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
typedef  int qboolean ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  COM_DefaultExtension (char*,int,char*) ; 
 int /*<<< orphan*/  Cbuf_InsertText (char*) ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*,...) ; 
 int /*<<< orphan*/  FS_FreeFile (void*) ; 
 int /*<<< orphan*/  FS_ReadFile (char*,void**) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 

void Cmd_Exec_f( void ) {
	qboolean quiet;
	union {
		char	*c;
		void	*v;
	} f;
	char	filename[MAX_QPATH];

	quiet = !Q_stricmp(Cmd_Argv(0), "execq");

	if (Cmd_Argc () != 2) {
		Com_Printf ("exec%s <filename> : execute a script file%s\n",
		            quiet ? "q" : "", quiet ? " without notification" : "");
		return;
	}

	Q_strncpyz( filename, Cmd_Argv(1), sizeof( filename ) );
	COM_DefaultExtension( filename, sizeof( filename ), ".cfg" );
	FS_ReadFile( filename, &f.v);
	if (!f.c) {
		Com_Printf ("couldn't exec %s\n", filename);
		return;
	}
	if (!quiet)
		Com_Printf ("execing %s\n", filename);
	
	Cbuf_InsertText (f.c);

	FS_FreeFile (f.v);
}