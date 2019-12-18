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
typedef  int /*<<< orphan*/  uint32_t ;
struct bhyvegc_image {int width; int height; int /*<<< orphan*/ * data; } ;
struct bhyvegc {int /*<<< orphan*/  raw; struct bhyvegc_image* gc_image; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * reallocarray (int /*<<< orphan*/ *,int,int) ; 

void
bhyvegc_resize(struct bhyvegc *gc, int width, int height)
{
	struct bhyvegc_image *gc_image;

	gc_image = gc->gc_image;

	gc_image->width = width;
	gc_image->height = height;
	if (!gc->raw) {
		gc_image->data = reallocarray(gc_image->data, width * height,
		    sizeof (uint32_t));
		if (gc_image->data != NULL)
			memset(gc_image->data, 0, width * height *
			    sizeof (uint32_t));
	}
}