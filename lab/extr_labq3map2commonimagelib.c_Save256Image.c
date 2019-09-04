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
 int /*<<< orphan*/  ExtractFileExtension (char const*,char*) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  WriteLBMfile (char const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WritePCXfile (char const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

void Save256Image( const char *name, byte *pixels, byte *palette,
				   int width, int height ){
	char ext[128];

	ExtractFileExtension( name, ext );
	if ( !Q_stricmp( ext, "lbm" ) ) {
		WriteLBMfile( name, pixels, width, height, palette );
	}
	else if ( !Q_stricmp( ext, "pcx" ) ) {
		WritePCXfile( name, pixels, width, height, palette );
	}
	else{
		Error( "%s doesn't have a known image extension", name );
	}
}