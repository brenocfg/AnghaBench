#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int keynum; scalar_t__ name; } ;
typedef  TYPE_1__ keyname_t ;

/* Variables and functions */
 int Com_HexStrToInt (char*) ; 
 int /*<<< orphan*/  Q_stricmp (char*,scalar_t__) ; 
 TYPE_1__* keynames ; 
 int strlen (char*) ; 
 int tolower (char) ; 

int Key_StringToKeynum( char *str ) {
	keyname_t	*kn;
	
	if ( !str || !str[0] ) {
		return -1;
	}
	if ( !str[1] ) {
		return tolower( str[0] );
	}

	// check for hex code
	if ( strlen( str ) == 4 ) {
		int n = Com_HexStrToInt( str );

		if ( n >= 0 ) {
			return n;
		}
	}

	// scan for a text match
	for ( kn=keynames ; kn->name ; kn++ ) {
		if ( !Q_stricmp( str,kn->name ) )
			return kn->keynum;
	}

	return -1;
}