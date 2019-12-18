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

/* Variables and functions */
 int /*<<< orphan*/  MD5 (char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  SetKeyValue (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * entities ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void EmitVertexRemapShader( char *from, char *to ){
	byte digest[ 16 ];
	char key[ 64 ], value[ 256 ];


	/* dummy check */
	if ( from == NULL || from[ 0 ] == '\0' ||
		 to == NULL || to[ 0 ] == '\0' ) {
		return;
	}

	/* build value */
	sprintf( value, "%s;%s", from, to );

	/* make md5 hash */
	MD5( value, strlen( value ), (unsigned char *) &digest );

	/* make key (this is annoying, as vertexremapshader is precisely 17 characters,
	   which is one too long, so we leave off the last byte of the md5 digest) */
	sprintf( key, "vertexremapshader%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
			 digest[ 0 ], digest[ 1 ], digest[ 2 ], digest[ 3 ], digest[ 4 ], digest[ 5 ], digest[ 6 ], digest[ 7 ],
			 digest[ 8 ], digest[ 9 ], digest[ 10 ], digest[ 11 ], digest[ 12 ], digest[ 13 ], digest[ 14 ] ); /* no: digest[ 15 ] */

	/* add key/value pair to worldspawn */
	SetKeyValue( &entities[ 0 ], key, value );
}