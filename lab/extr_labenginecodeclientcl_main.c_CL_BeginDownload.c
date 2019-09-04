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
struct TYPE_4__ {scalar_t__ downloadCount; scalar_t__ downloadBlock; int /*<<< orphan*/  downloadTempName; int /*<<< orphan*/  downloadName; } ;
struct TYPE_3__ {int /*<<< orphan*/  realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AddReliableCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  Com_sprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char const*) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_2__ clc ; 
 TYPE_1__ cls ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  va (char*,char const*) ; 

void CL_BeginDownload( const char *localName, const char *remoteName ) {

	Com_DPrintf("***** CL_BeginDownload *****\n"
				"Localname: %s\n"
				"Remotename: %s\n"
				"****************************\n", localName, remoteName);

	Q_strncpyz ( clc.downloadName, localName, sizeof(clc.downloadName) );
	Com_sprintf( clc.downloadTempName, sizeof(clc.downloadTempName), "%s.tmp", localName );

	// Set so UI gets access to it
	Cvar_Set( "cl_downloadName", remoteName );
	Cvar_Set( "cl_downloadSize", "0" );
	Cvar_Set( "cl_downloadCount", "0" );
	Cvar_SetValue( "cl_downloadTime", cls.realtime );

	clc.downloadBlock = 0; // Starting new file
	clc.downloadCount = 0;

	CL_AddReliableCommand(va("download %s", remoteName), qfalse);
}