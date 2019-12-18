#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ refCount; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ * pixels; int /*<<< orphan*/ * filename; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ image_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numImages ; 

void ImageFree( image_t *image ){
	/* dummy check */
	if ( image == NULL ) {
		return;
	}

	/* decrement refcount */
	image->refCount--;

	/* free? */
	if ( image->refCount <= 0 ) {
		if ( image->name != NULL ) {
			free( image->name );
		}
		image->name = NULL;
		if ( image->filename != NULL ) {
			free( image->filename );
		}
		image->filename = NULL;
		free( image->pixels );
		image->width = 0;
		image->height = 0;
		numImages--;
	}
}