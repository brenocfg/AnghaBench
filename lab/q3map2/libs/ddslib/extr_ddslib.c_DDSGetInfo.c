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
typedef  int /*<<< orphan*/  ddsPF_t ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  size; scalar_t__ magic; } ;
typedef  TYPE_1__ ddsBuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DDSDecodePixelFormat (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int DDSLittleLong (int /*<<< orphan*/ ) ; 

int DDSGetInfo( ddsBuffer_t *dds, int *width, int *height, ddsPF_t *pf ){
	/* dummy test */
	if ( dds == NULL ) {
		return -1;
	}

	/* test dds header */
	if ( *( (int*) dds->magic ) != *( (int*) "DDS " ) ) {
		return -1;
	}
	if ( DDSLittleLong( dds->size ) != 124 ) {
		return -1;
	}

	/* extract width and height */
	if ( width != NULL ) {
		*width = DDSLittleLong( dds->width );
	}
	if ( height != NULL ) {
		*height = DDSLittleLong( dds->height );
	}

	/* get pixel format */
	DDSDecodePixelFormat( dds, pf );

	/* return ok */
	return 0;
}