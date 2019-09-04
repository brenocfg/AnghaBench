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
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_2__ {char* buffer; int /*<<< orphan*/  scroll; int /*<<< orphan*/  cursor; } ;

/* Variables and functions */
 int COMMAND_HISTORY ; 
 int /*<<< orphan*/  CONSOLE_HISTORY_FILE ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_FCloseFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_FOpenFileWrite (int /*<<< orphan*/ ) ; 
 int FS_Write (char*,int,int /*<<< orphan*/ ) ; 
 int MAX_CONSOLE_SAVE_BUFFER ; 
 int /*<<< orphan*/  Q_strcat (char*,int,int /*<<< orphan*/ ) ; 
 char* consoleSaveBuffer ; 
 int consoleSaveBufferSize ; 
 TYPE_1__* historyEditLines ; 
 int nextHistoryLine ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

void CL_SaveConsoleHistory( void )
{
	int						i;
	int						lineLength, saveBufferLength, additionalLength;
	fileHandle_t	f;

	consoleSaveBuffer[ 0 ] = '\0';

	i = ( nextHistoryLine - 1 ) % COMMAND_HISTORY;
	do
	{
		if( historyEditLines[ i ].buffer[ 0 ] )
		{
			lineLength = strlen( historyEditLines[ i ].buffer );
			saveBufferLength = strlen( consoleSaveBuffer );

			//ICK
			additionalLength = lineLength + strlen( "999 999 999  " );

			if( saveBufferLength + additionalLength < MAX_CONSOLE_SAVE_BUFFER )
			{
				Q_strcat( consoleSaveBuffer, MAX_CONSOLE_SAVE_BUFFER,
						va( "%d %d %d %s ",
						historyEditLines[ i ].cursor,
						historyEditLines[ i ].scroll,
						lineLength,
						historyEditLines[ i ].buffer ) );
			}
			else
				break;
		}
		i = ( i - 1 + COMMAND_HISTORY ) % COMMAND_HISTORY;
	}
	while( i != ( nextHistoryLine - 1 ) % COMMAND_HISTORY );

	consoleSaveBufferSize = strlen( consoleSaveBuffer );

	f = FS_FOpenFileWrite( CONSOLE_HISTORY_FILE );
	if( !f )
	{
		Com_Printf( "Couldn't write %s.\n", CONSOLE_HISTORY_FILE );
		return;
	}

	if( FS_Write( consoleSaveBuffer, consoleSaveBufferSize, f ) < consoleSaveBufferSize )
		Com_Printf( "Couldn't write %s.\n", CONSOLE_HISTORY_FILE );

	FS_FCloseFile( f );
}