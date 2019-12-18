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
 char const* lineBuffer ; 
 int lineParseOffset ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char const*,int) ; 
 scalar_t__* token ; 

__attribute__((used)) static qboolean Parse( void ) {
	/* Hand-optimized by PhaethonH */
	const char 	*p, *q;

	/* Because lineParseOffset is only updated just before exit, this makes this code version somewhat harder to debug under a symbolic debugger. */

	*token = 0;  /* Clear token. */

	// skip whitespace
	for (p = lineBuffer + lineParseOffset; *p && (*p <= ' '); p++) /* nop */ ;

	// skip ; comments
	/* die on end-of-string */
	if ((*p == ';') || (*p == 0)) {
		lineParseOffset = p - lineBuffer;
		return qfalse;
	}

	q = p;  /* Mark the start of token. */
	/* Find separator first. */
	for ( ; *p > 32; p++) /* nop */ ;  /* XXX: unsafe assumptions. */
	/* *p now sits on separator.  Mangle other values accordingly. */
	strncpy(token, q, p - q);
	token[p - q] = 0;

	lineParseOffset = p - lineBuffer;

	return qtrue;
}