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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char const*) ; 
 int /*<<< orphan*/  LoadTGABuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int*) ; 
 int vfsLoadFile (char*,void**,int /*<<< orphan*/ ) ; 

void LoadTGA( const char *name, byte **pixels, int *width, int *height ){
	byte            *buffer;
	int nLen;
	//
	// load the file
	//
	nLen = vfsLoadFile( ( char * ) name, (void **)&buffer, 0 );
	if ( nLen == -1 ) {
		Error( "Couldn't read %s", name );
	}

	LoadTGABuffer( buffer, buffer + nLen, pixels, width, height );

}