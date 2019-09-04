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
 char* COM_Parse (char*) ; 
 int /*<<< orphan*/  DefaultExtension (char*,char*) ; 
 int /*<<< orphan*/  LoadFile (char*,void**) ; 
 int MAX_OS_PATH ; 
 int /*<<< orphan*/ * asmFileNames ; 
 char const* com_token ; 
 int /*<<< orphan*/  copystring (char const*) ; 
 size_t numAsmFiles ; 
 char* outputFilename ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static void ParseOptionFile( const char *filename ) {
	char		expanded[MAX_OS_PATH];
	char		*text, *text_p;

	strcpy( expanded, filename );
	DefaultExtension( expanded, ".q3asm" );
	LoadFile( expanded, (void **)&text );
	if ( !text ) {
		return;
	}

	text_p = text;

	while( ( text_p = COM_Parse( text_p ) ) != 0 ) {
		if ( !strcmp( com_token, "-o" ) ) {
			// allow output override in option file
			text_p = COM_Parse( text_p );
			if ( text_p ) {
				strcpy( outputFilename, com_token );
			}
			continue;
		}

		asmFileNames[ numAsmFiles ] = copystring( com_token );
		numAsmFiles++;
	}
}