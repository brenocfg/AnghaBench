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
typedef  int /*<<< orphan*/  mfield_t ;

/* Variables and functions */
 int /*<<< orphan*/  MField_CharEvent (int /*<<< orphan*/ *,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trap_GetClipboardData (char*,int) ; 

void MField_Paste( mfield_t *edit ) {
	char	pasteBuffer[64];
	int		pasteLen, i;

	trap_GetClipboardData( pasteBuffer, 64 );

	// send as if typed, so insert / overstrike works properly
	pasteLen = strlen( pasteBuffer );
	for ( i = 0 ; i < pasteLen ; i++ ) {
		MField_CharEvent( edit, pasteBuffer[i] );
	}
}