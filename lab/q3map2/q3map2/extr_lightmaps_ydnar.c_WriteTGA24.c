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
typedef  scalar_t__ qboolean ;
typedef  int byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  fwrite (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* safe_malloc (int) ; 

void WriteTGA24( char *filename, byte *data, int width, int height, qboolean flip ){
	int i, c;
	byte    *buffer, *in;
	FILE    *file;


	/* allocate a buffer and set it up */
	buffer = safe_malloc( width * height * 3 + 18 );
	memset( buffer, 0, 18 );
	buffer[ 2 ] = 2;
	buffer[ 12 ] = width & 255;
	buffer[ 13 ] = width >> 8;
	buffer[ 14 ] = height & 255;
	buffer[ 15 ] = height >> 8;
	buffer[ 16 ] = 24;

	/* swap rgb to bgr */
	c = ( width * height * 3 ) + 18;
	for ( i = 18; i < c; i += 3 )
	{
		buffer[ i ] = data[ i - 18 + 2 ];       /* blue */
		buffer[ i + 1 ] = data[ i - 18 + 1 ];   /* green */
		buffer[ i + 2 ] = data[ i - 18 + 0 ];   /* red */
	}

	/* write it and free the buffer */
	file = fopen( filename, "wb" );
	if ( file == NULL ) {
		Error( "Unable to open %s for writing", filename );
	}

	/* flip vertically? */
	if ( flip ) {
		fwrite( buffer, 1, 18, file );
		for ( in = buffer + ( ( height - 1 ) * width * 3 ) + 18; in >= buffer; in -= ( width * 3 ) )
			fwrite( in, 1, ( width * 3 ), file );
	}
	else{
		fwrite( buffer, 1, c, file );
	}

	/* close the file */
	fclose( file );
	free( buffer );
}