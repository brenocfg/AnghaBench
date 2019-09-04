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

/* Variables and functions */
 int strlen (char const*) ; 

__attribute__((used)) static int UI_CDKeyMenu_PreValidateKey( const char *key ) {
	char	ch;

	if( strlen( key ) != 16 ) {
		return 1;
	}

	while( ( ch = *key++ ) ) {
		switch( ch ) {
		case '2':
		case '3':
		case '7':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'g':
		case 'h':
		case 'j':
		case 'l':
		case 'p':
		case 'r':
		case 's':
		case 't':
		case 'w':
			continue;
		default:
			return -1;
		}
	}

	return 0;
}