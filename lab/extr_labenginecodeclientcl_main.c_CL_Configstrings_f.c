#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* stringOffsets; scalar_t__ stringData; } ;
struct TYPE_6__ {TYPE_1__ gameState; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int MAX_CONFIGSTRINGS ; 
 TYPE_3__ cl ; 
 TYPE_2__ clc ; 

void CL_Configstrings_f( void ) {
	int		i;
	int		ofs;

	if ( clc.state != CA_ACTIVE ) {
		Com_Printf( "Not connected to a server.\n");
		return;
	}

	for ( i = 0 ; i < MAX_CONFIGSTRINGS ; i++ ) {
		ofs = cl.gameState.stringOffsets[ i ];
		if ( !ofs ) {
			continue;
		}
		Com_Printf( "%4i: %s\n", i, cl.gameState.stringData + ofs );
	}
}