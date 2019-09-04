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
struct TYPE_4__ {int /*<<< orphan*/  texnum; int /*<<< orphan*/  imgName; struct TYPE_4__* next; } ;
typedef  TYPE_1__ image_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  Upload32 (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long generateHashValue (char const*) ; 
 TYPE_1__** hashTable ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qglBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

bool dmlab_update_rgba_texture( const char* name, int width, int height, const unsigned char* data ) {
	image_t* image;
	long hash = generateHashValue(name);
	for (image=hashTable[hash]; image; image=image->next) {
		if ( !strcmp( name, image->imgName ) ) {
			qglBindTexture( GL_TEXTURE_2D,  image->texnum );
			Upload32( (unsigned char*)data, 0, 0, width, height,
								GL_RGBA8,
								1,
								image,
								qfalse,
								qfalse );
			return true;
		}
	}
	return false;
}