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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int filelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  print (char*,char const*) ; 
 scalar_t__* sourceFile ; 
 int sourceLine ; 
 scalar_t__* sourcePtr ; 

__attribute__((used)) static void LoadSourceFile( const char *filename ) {
	FILE	*f;
	int		length;

	f = fopen( filename, "r" );
	if ( !f ) {
		print( ";couldn't open %s\n", filename );
		sourceFile = NULL;
		return;
	}
	length = filelength( f );
	sourceFile = malloc( length + 1 );
	if ( sourceFile ) {
		fread( sourceFile, length, 1, f );
		sourceFile[length] = 0;
	}

	fclose( f );
	sourceLine = 1;
	sourcePtr = sourceFile;
}