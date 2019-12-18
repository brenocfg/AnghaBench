#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ddsPF_t ;
struct TYPE_4__ {unsigned int fourCC; } ;
struct TYPE_5__ {TYPE_1__ pixelFormat; } ;
typedef  TYPE_2__ ddsBuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DDS_PF_ARGB8888 ; 
 int /*<<< orphan*/  DDS_PF_DXT1 ; 
 int /*<<< orphan*/  DDS_PF_DXT2 ; 
 int /*<<< orphan*/  DDS_PF_DXT3 ; 
 int /*<<< orphan*/  DDS_PF_DXT4 ; 
 int /*<<< orphan*/  DDS_PF_DXT5 ; 
 int /*<<< orphan*/  DDS_PF_UNKNOWN ; 

__attribute__((used)) static void DDSDecodePixelFormat( ddsBuffer_t *dds, ddsPF_t *pf ){
	unsigned int fourCC;


	/* dummy check */
	if ( dds == NULL || pf == NULL ) {
		return;
	}

	/* extract fourCC */
	fourCC = dds->pixelFormat.fourCC;

	/* test it */
	if ( fourCC == 0 ) {
		*pf = DDS_PF_ARGB8888;
	}
	else if ( fourCC == *( (unsigned int*) "DXT1" ) ) {
		*pf = DDS_PF_DXT1;
	}
	else if ( fourCC == *( (unsigned int*) "DXT2" ) ) {
		*pf = DDS_PF_DXT2;
	}
	else if ( fourCC == *( (unsigned int*) "DXT3" ) ) {
		*pf = DDS_PF_DXT3;
	}
	else if ( fourCC == *( (unsigned int*) "DXT4" ) ) {
		*pf = DDS_PF_DXT4;
	}
	else if ( fourCC == *( (unsigned int*) "DXT5" ) ) {
		*pf = DDS_PF_DXT5;
	}
	else{
		*pf = DDS_PF_UNKNOWN;
	}
}