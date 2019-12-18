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
 int /*<<< orphan*/  CodeError (char*) ; 
 int MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  currentFileLine ; 
 scalar_t__* lineBuffer ; 
 scalar_t__ lineParseOffset ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 scalar_t__* token ; 

__attribute__((used)) static char *ExtractLine( char *data ) {
/* Goal:
	 Given a string `data', extract one text line into buffer `lineBuffer' that
	 is no longer than MAX_LINE_LENGTH characters long.  Return value is
	 remainder of `data' that isn't part of `lineBuffer'.
 -PH
*/
	/* Hand-optimized by PhaethonH */
	char 	*p, *q;

	currentFileLine++;

	lineParseOffset = 0;
	token[0] = 0;
	*lineBuffer = 0;

	p = q = data;
	if (!*q) {
		return NULL;
	}

	for ( ; !((*p == 0) || (*p == '\n')); p++)  /* nop */ ;

	if ((p - q) >= MAX_LINE_LENGTH) {
		CodeError( "MAX_LINE_LENGTH" );
		return data;
	}

	memcpy( lineBuffer, data, (p - data) );
	lineBuffer[(p - data)] = 0;
	p += (*p == '\n') ? 1 : 0;  /* Skip over final newline. */
	return p;
}