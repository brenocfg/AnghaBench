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
struct TYPE_3__ {char* name; int keynum; } ;
typedef  TYPE_1__ keyname_t ;

/* Variables and functions */
 int MAX_KEYS ; 
 TYPE_1__* keynames ; 

char *Key_KeynumToString( int keynum ) {
	keyname_t	*kn;	
	static	char	tinystr[5];
	int			i, j;

	if ( keynum == -1 ) {
		return "<KEY NOT FOUND>";
	}

	if ( keynum < 0 || keynum >= MAX_KEYS ) {
		return "<OUT OF RANGE>";
	}

	// check for printable ascii (don't use quote)
	if ( keynum > 32 && keynum < 127 && keynum != '"' && keynum != ';' ) {
		tinystr[0] = keynum;
		tinystr[1] = 0;
		return tinystr;
	}

	// check for a key string
	for ( kn=keynames ; kn->name ; kn++ ) {
		if (keynum == kn->keynum) {
			return kn->name;
		}
	}

	// make a hex string
	i = keynum >> 4;
	j = keynum & 15;

	tinystr[0] = '0';
	tinystr[1] = 'x';
	tinystr[2] = i > 9 ? i - 10 + 'a' : i + '0';
	tinystr[3] = j > 9 ? j - 10 + 'a' : j + '0';
	tinystr[4] = 0;

	return tinystr;
}