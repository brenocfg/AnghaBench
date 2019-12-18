#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ image_t ;

/* Variables and functions */
 int /*<<< orphan*/  ImageInit () ; 
 int MAX_IMAGES ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 TYPE_1__* images ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

image_t *ImageFind( const char *filename ){
	int i;
	char name[ 1024 ];


	/* init */
	ImageInit();

	/* dummy check */
	if ( filename == NULL || filename[ 0 ] == '\0' ) {
		return NULL;
	}

	/* strip file extension off name */
	strcpy( name, filename );
	StripExtension( name );

	/* search list */
	for ( i = 0; i < MAX_IMAGES; i++ )
	{
		if ( images[ i ].name != NULL && !strcmp( name, images[ i ].name ) ) {
			return &images[ i ];
		}
	}

	/* no matching image found */
	return NULL;
}