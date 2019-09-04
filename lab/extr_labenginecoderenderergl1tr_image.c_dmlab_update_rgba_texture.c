#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_4__ {int flags; int uploadWidth; int uploadHeight; int /*<<< orphan*/  uploadMips; int /*<<< orphan*/  internalFormat; int /*<<< orphan*/  texnum; int /*<<< orphan*/  imgName; struct TYPE_4__* next; } ;
typedef  TYPE_1__ image_t ;
struct TYPE_5__ {size_t currenttmu; int /*<<< orphan*/ * currenttextures; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int IMGFLAG_MIPMAP ; 
 int IMGFLAG_PICMIP ; 
 int /*<<< orphan*/  Upload32 (unsigned int*,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 long generateHashValue (char const*) ; 
 TYPE_3__ glState ; 
 TYPE_1__** hashTable ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qglBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

bool dmlab_update_rgba_texture( const char* name, int width, int height, const unsigned char* data ) {
	image_t* image;
	long hash = generateHashValue(name);
	for (image=hashTable[hash]; image; image=image->next) {
		if ( !strcmp( name, image->imgName ) ) {
			qboolean picmip = image->flags & IMGFLAG_PICMIP;
			qboolean mipmap = image->flags & IMGFLAG_MIPMAP;
      qboolean capMaxSize = width != image->uploadWidth || height !=image-> uploadHeight;
			glState.currenttextures[glState.currenttmu] = image->texnum;
			qglBindTexture( GL_TEXTURE_2D,  image->texnum );
			Upload32( (unsigned *)data, width, height, 0, mipmap, picmip, qfalse, qfalse, capMaxSize,
								&image->internalFormat,
								&image->uploadWidth,
								&image->uploadHeight,
								&image->uploadMips );
			return true;
		}
	}
	return false;
}