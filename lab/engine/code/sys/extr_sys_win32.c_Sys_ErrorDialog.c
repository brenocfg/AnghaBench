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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_TEXT ; 
 unsigned int CON_LogRead (char*,int) ; 
 scalar_t__ CON_LogSize () ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  Com_Memcpy (char*,char*,unsigned int) ; 
 scalar_t__ DR_YES ; 
 int /*<<< orphan*/  DT_YES_NO ; 
 scalar_t__ EmptyClipboard () ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int,scalar_t__) ; 
 scalar_t__ GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (char*) ; 
 scalar_t__ OpenClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Sys_Dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  va (char*,char const*) ; 

void Sys_ErrorDialog( const char *error )
{
	if( Sys_Dialog( DT_YES_NO, va( "%s. Copy console log to clipboard?", error ),
			"Error" ) == DR_YES )
	{
		HGLOBAL memoryHandle;
		char *clipMemory;

		memoryHandle = GlobalAlloc( GMEM_MOVEABLE|GMEM_DDESHARE, CON_LogSize( ) + 1 );
		clipMemory = (char *)GlobalLock( memoryHandle );

		if( clipMemory )
		{
			char *p = clipMemory;
			char buffer[ 1024 ];
			unsigned int size;

			while( ( size = CON_LogRead( buffer, sizeof( buffer ) ) ) > 0 )
			{
				Com_Memcpy( p, buffer, size );
				p += size;
			}

			*p = '\0';

			if( OpenClipboard( NULL ) && EmptyClipboard( ) )
				SetClipboardData( CF_TEXT, memoryHandle );

			GlobalUnlock( clipMemory );
			CloseClipboard( );
		}
	}
}