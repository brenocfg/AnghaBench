#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {int /*<<< orphan*/  (* ImageLoader ) (char*,int /*<<< orphan*/ **,int*,int*) ;int /*<<< orphan*/  ext; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char const*,char*) ;} ;

/* Variables and functions */
 char* COM_GetExtension (char*) ; 
 int /*<<< orphan*/  COM_StripExtension (char const*,char*,int) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  PRINT_DEVELOPER ; 
 int /*<<< orphan*/  Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 TYPE_2__* imageLoaders ; 
 int numImageLoaders ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* va (char*,char*,int /*<<< orphan*/ ) ; 

void R_LoadImage( const char *name, byte **pic, int *width, int *height )
{
	qboolean orgNameFailed = qfalse;
	int orgLoader = -1;
	int i;
	char localName[ MAX_QPATH ];
	const char *ext;
	char *altName;

	*pic = NULL;
	*width = 0;
	*height = 0;

	Q_strncpyz( localName, name, MAX_QPATH );

	ext = COM_GetExtension( localName );

	if( *ext )
	{
		// Look for the correct loader and use it
		for( i = 0; i < numImageLoaders; i++ )
		{
			if( !Q_stricmp( ext, imageLoaders[ i ].ext ) )
			{
				// Load
				imageLoaders[ i ].ImageLoader( localName, pic, width, height );
				break;
			}
		}

		// A loader was found
		if( i < numImageLoaders )
		{
			if( *pic == NULL )
			{
				// Loader failed, most likely because the file isn't there;
				// try again without the extension
				orgNameFailed = qtrue;
				orgLoader = i;
				COM_StripExtension( name, localName, MAX_QPATH );
			}
			else
			{
				// Something loaded
				return;
			}
		}
	}

	// Try and find a suitable match using all
	// the image formats supported
	for( i = 0; i < numImageLoaders; i++ )
	{
		if (i == orgLoader)
			continue;

		altName = va( "%s.%s", localName, imageLoaders[ i ].ext );

		// Load
		imageLoaders[ i ].ImageLoader( altName, pic, width, height );

		if( *pic )
		{
			if( orgNameFailed )
			{
				ri.Printf( PRINT_DEVELOPER, "WARNING: %s not present, using %s instead\n",
						name, altName );
			}

			break;
		}
	}
}