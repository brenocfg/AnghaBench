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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int strlen (char const*) ; 

qboolean StringIsInteger( const char * s ) {
	int			i;
	int			len;
	qboolean	foundDigit;

	len = strlen( s );
	foundDigit = qfalse;

	for ( i=0 ; i < len ; i++ ) {
		if ( !isdigit( s[i] ) ) {
			return qfalse;
		}

		foundDigit = qtrue;
	}

	return foundDigit;
}