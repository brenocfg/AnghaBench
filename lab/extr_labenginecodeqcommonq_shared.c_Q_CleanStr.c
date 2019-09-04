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
 scalar_t__ Q_IsColorString (char*) ; 

char *Q_CleanStr( char *string ) {
	char*	d;
	char*	s;
	int		c;

	s = string;
	d = string;
	while ((c = *s) != 0 ) {
		if ( Q_IsColorString( s ) ) {
			s++;
		}		
		else if ( c >= 0x20 && c <= 0x7E ) {
			*d++ = c;
		}
		s++;
	}
	*d = '\0';

	return string;
}