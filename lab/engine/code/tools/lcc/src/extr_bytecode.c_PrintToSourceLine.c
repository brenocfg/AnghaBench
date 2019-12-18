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
 int /*<<< orphan*/  print (char*,int,char*) ; 
 int /*<<< orphan*/  sourceFile ; 
 int sourceLine ; 
 char* sourcePtr ; 

__attribute__((used)) static void PrintToSourceLine( int line ) {
	int		c;

	if ( !sourceFile ) {
		return;
	}
	while ( sourceLine <= line ) {
		int		i;

		for ( i = 0 ; sourcePtr[i] && sourcePtr[i] != '\n' ; i++ ) {
		}
		c = sourcePtr[i];
		if ( c == '\n' ) {
			sourcePtr[i] = 0;
		}
		print( ";%d:%s\n", sourceLine, sourcePtr );
		if ( c == 0 ) {
			sourcePtr += i;	// end of file
		} else {
			sourcePtr += i+1;
		}
		sourceLine++;
	}
}