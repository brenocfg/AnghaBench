#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int refCount; char* name; scalar_t__ width; scalar_t__ height; char* filename; int /*<<< orphan*/ * pixels; } ;
typedef  TYPE_1__ image_t ;
typedef  int /*<<< orphan*/  ddsPF_t ;
typedef  int /*<<< orphan*/  ddsBuffer_t ;
typedef  char byte ;

/* Variables and functions */
 int /*<<< orphan*/  DDSGetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 TYPE_1__* ImageFind (char*) ; 
 int /*<<< orphan*/  ImageInit () ; 
 int /*<<< orphan*/  LoadDDSBuffer (char*,int,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*) ; 
 int LoadJPGBuff (char*,int,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  LoadPNGBuffer (char*,int,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  LoadTGABuffer (char*,char*,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*) ; 
 int MAX_IMAGES ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,unsigned char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteTGA (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* images ; 
 int /*<<< orphan*/  numImages ; 
 void* safe_malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 int vfsLoadFile (char const*,void**,int /*<<< orphan*/ ) ; 

image_t *ImageLoad( const char *filename ){
	int i;
	image_t     *image;
	char name[ 1024 ];
	int size;
	byte        *buffer = NULL;


	/* init */
	ImageInit();

	/* dummy check */
	if ( filename == NULL || filename[ 0 ] == '\0' ) {
		return NULL;
	}

	/* strip file extension off name */
	strcpy( name, filename );
	StripExtension( name );

	/* try to find existing image */
	image = ImageFind( name );
	if ( image != NULL ) {
		image->refCount++;
		return image;
	}

	/* none found, so find first non-null image */
	image = NULL;
	for ( i = 0; i < MAX_IMAGES; i++ )
	{
		if ( images[ i ].name == NULL ) {
			image = &images[ i ];
			break;
		}
	}

	/* too many images? */
	if ( image == NULL ) {
		Error( "MAX_IMAGES (%d) exceeded, there are too many image files referenced by the map.", MAX_IMAGES );
	}

	/* set it up */
	image->name = safe_malloc( strlen( name ) + 1 );
	strcpy( image->name, name );

	/* attempt to load tga */
	StripExtension( name );
	strcat( name, ".tga" );
	size = vfsLoadFile( (const char*) name, (void**) &buffer, 0 );
	if ( size > 0 ) {
		LoadTGABuffer( buffer, buffer + size, &image->pixels, &image->width, &image->height );
	}
	else
	{
		/* attempt to load png */
		StripExtension( name );
		strcat( name, ".png" );
		size = vfsLoadFile( (const char*) name, (void**) &buffer, 0 );
		if ( size > 0 ) {
			LoadPNGBuffer( buffer, size, &image->pixels, &image->width, &image->height );
		}
		else
		{
			/* attempt to load jpg */
			StripExtension( name );
			strcat( name, ".jpg" );
			size = vfsLoadFile( (const char*) name, (void**) &buffer, 0 );
			if ( size > 0 ) {
				if ( LoadJPGBuff( buffer, size, &image->pixels, &image->width, &image->height ) == -1 && image->pixels != NULL ) {
					Sys_FPrintf( SYS_WRN, "WARNING: LoadJPGBuff: %s\n", (unsigned char*) image->pixels );
				}
			}
			else
			{
				/* attempt to load dds */
				StripExtension( name );
				strcat( name, ".dds" );
				size = vfsLoadFile( (const char*) name, (void**) &buffer, 0 );
				if ( size > 0 ) {
					LoadDDSBuffer( buffer, size, &image->pixels, &image->width, &image->height );

					/* debug code */
					#if 1
					{
						ddsPF_t pf;
						DDSGetInfo( (ddsBuffer_t*) buffer, NULL, NULL, &pf );
						Sys_Printf( "pf = %d\n", pf );
						if ( image->width > 0 ) {
							StripExtension( name );
							strcat( name, "_converted.tga" );
							WriteTGA( "C:\\games\\quake3\\baseq3\\textures\\rad\\dds_converted.tga", image->pixels, image->width, image->height );
						}
					}
					#endif
				}
			}
		}
	}

	/* free file buffer */
	free( buffer );

	/* make sure everything's kosher */
	if ( size <= 0 || image->width <= 0 || image->height <= 0 || image->pixels == NULL ) {
		//%	Sys_Printf( "size = %d  width = %d  height = %d  pixels = 0x%08x (%s)\n",
		//%		size, image->width, image->height, image->pixels, name );
		free( image->name );
		image->name = NULL;
		return NULL;
	}

	/* set filename */
	image->filename = safe_malloc( strlen( name ) + 1 );
	strcpy( image->filename, name );

	/* set count */
	image->refCount = 1;
	numImages++;

	/* return the image */
	return image;
}