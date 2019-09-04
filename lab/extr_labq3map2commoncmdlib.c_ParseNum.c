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
 int ParseHex (char const*) ; 
 int atol (char const*) ; 

int ParseNum( const char *str ){
	if ( str[0] == '$' ) {
		return ParseHex( str + 1 );
	}
	if ( str[0] == '0' && str[1] == 'x' ) {
		return ParseHex( str + 2 );
	}
	return atol( str );
}