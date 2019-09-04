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
typedef  int /*<<< orphan*/  st ;
struct TYPE_5__ {TYPE_1__* pack; struct TYPE_5__* next; } ;
typedef  TYPE_2__ searchpath_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {scalar_t__ checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASEGAME ; 
 int /*<<< orphan*/  BASETA ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*,scalar_t__) ; 
 scalar_t__ FS_CheckDirTraversal (char*) ; 
 scalar_t__ FS_SV_FileExists (int /*<<< orphan*/ ) ; 
 scalar_t__ FS_idPak (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_ZPATH ; 
 int /*<<< orphan*/  NUM_ID_PAKS ; 
 int /*<<< orphan*/  NUM_TA_PAKS ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char*) ; 
 int fs_numServerReferencedPaks ; 
 TYPE_2__* fs_searchpaths ; 
 char** fs_serverReferencedPakNames ; 
 scalar_t__* fs_serverReferencedPaks ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

qboolean FS_ComparePaks( char *neededpaks, int len, qboolean dlstring ) {
	searchpath_t	*sp;
	qboolean havepak;
	char *origpos = neededpaks;
	int i;

	if (!fs_numServerReferencedPaks)
		return qfalse; // Server didn't send any pack information along

	*neededpaks = 0;

	for ( i = 0 ; i < fs_numServerReferencedPaks ; i++ )
	{
		// Ok, see if we have this pak file
		havepak = qfalse;

		// never autodownload any of the id paks
		if(FS_idPak(fs_serverReferencedPakNames[i], BASEGAME, NUM_ID_PAKS)
#ifndef STANDALONE
				|| FS_idPak(fs_serverReferencedPakNames[i], BASETA, NUM_TA_PAKS)
#endif
			)
		{
			continue;
		}

		// Make sure the server cannot make us write to non-quake3 directories.
		if(FS_CheckDirTraversal(fs_serverReferencedPakNames[i]))
		{
			Com_Printf("WARNING: Invalid download name %s\n", fs_serverReferencedPakNames[i]);
			continue;
		}

		for ( sp = fs_searchpaths ; sp ; sp = sp->next ) {
			if ( sp->pack && sp->pack->checksum == fs_serverReferencedPaks[i] ) {
				havepak = qtrue; // This is it!
				break;
			}
		}

		if ( !havepak && fs_serverReferencedPakNames[i] && *fs_serverReferencedPakNames[i] ) { 
			// Don't got it

			if (dlstring)
			{
				// We need this to make sure we won't hit the end of the buffer or the server could
				// overwrite non-pk3 files on clients by writing so much crap into neededpaks that
				// Q_strcat cuts off the .pk3 extension.

				origpos += strlen(origpos);

				// Remote name
				Q_strcat( neededpaks, len, "@");
				Q_strcat( neededpaks, len, fs_serverReferencedPakNames[i] );
				Q_strcat( neededpaks, len, ".pk3" );

				// Local name
				Q_strcat( neededpaks, len, "@");
				// Do we have one with the same name?
				if ( FS_SV_FileExists( va( "%s.pk3", fs_serverReferencedPakNames[i] ) ) )
				{
					char st[MAX_ZPATH];
					// We already have one called this, we need to download it to another name
					// Make something up with the checksum in it
					Com_sprintf( st, sizeof( st ), "%s.%08x.pk3", fs_serverReferencedPakNames[i], fs_serverReferencedPaks[i] );
					Q_strcat( neededpaks, len, st );
				}
				else
				{
					Q_strcat( neededpaks, len, fs_serverReferencedPakNames[i] );
					Q_strcat( neededpaks, len, ".pk3" );
				}

				// Find out whether it might have overflowed the buffer and don't add this file to the
				// list if that is the case.
				if(strlen(origpos) + (origpos - neededpaks) >= len - 1)
				{
					*origpos = '\0';
					break;
				}
			}
			else
			{
				Q_strcat( neededpaks, len, fs_serverReferencedPakNames[i] );
				Q_strcat( neededpaks, len, ".pk3" );
				// Do we have one with the same name?
				if ( FS_SV_FileExists( va( "%s.pk3", fs_serverReferencedPakNames[i] ) ) )
				{
					Q_strcat( neededpaks, len, " (local file exists with wrong checksum)");
				}
				Q_strcat( neededpaks, len, "\n");
			}
		}
	}

	if ( *neededpaks ) {
		return qtrue;
	}

	return qfalse; // We have them all
}