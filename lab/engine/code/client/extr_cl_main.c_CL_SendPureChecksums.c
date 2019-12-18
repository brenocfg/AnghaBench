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
typedef  int /*<<< orphan*/  cMsg ;
struct TYPE_2__ {int /*<<< orphan*/  serverId; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AddReliableCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_ReferencedPakPureChecksums () ; 
 int MAX_INFO_VALUE ; 
 TYPE_1__ cl ; 
 int /*<<< orphan*/  qfalse ; 

void CL_SendPureChecksums( void ) {
	char cMsg[MAX_INFO_VALUE];

	// if we are pure we need to send back a command with our referenced pk3 checksums
	Com_sprintf(cMsg, sizeof(cMsg), "cp %d %s", cl.serverId, FS_ReferencedPakPureChecksums());

	CL_AddReliableCommand(cMsg, qfalse);
}