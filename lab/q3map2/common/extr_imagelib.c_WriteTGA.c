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
typedef  int byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  fwrite (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* safe_malloc (int) ; 

void WriteTGA( const char *filename, byte *data, int width, int height ) {
	byte    *buffer;
	int i;
	int c;
	FILE    *f;

	buffer = safe_malloc( width * height * 4 + 18 );
	memset( buffer, 0, 18 );
	buffer[2] = 2;      // uncompressed type
	buffer[12] = width & 255;
	buffer[13] = width >> 8;
	buffer[14] = height & 255;
	buffer[15] = height >> 8;
	buffer[16] = 32;    // pixel size

	// swap rgb to bgr
	c = 18 + width * height * 4;
	for ( i = 18 ; i < c ; i += 4 )
	{
		buffer[i] = data[i - 18 + 2];       // blue
		buffer[i + 1] = data[i - 18 + 1];     // green
		buffer[i + 2] = data[i - 18 + 0];     // red
		buffer[i + 3] = data[i - 18 + 3];     // alpha
	}

	f = fopen( filename, "wb" );
	fwrite( buffer, 1, c, f );
	fclose( f );

	free( buffer );
}