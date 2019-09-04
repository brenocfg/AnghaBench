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
typedef  scalar_t__ ddsPF_t ;
typedef  int /*<<< orphan*/  ddsBuffer_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  DDSDecompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DDSGetInfo (int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 scalar_t__ DDS_PF_ARGB8888 ; 
 scalar_t__ DDS_PF_DXT1 ; 
 scalar_t__ DDS_PF_DXT3 ; 
 scalar_t__ DDS_PF_DXT5 ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * safe_malloc (int) ; 

__attribute__((used)) static void LoadDDSBuffer( byte *buffer, int size, byte **pixels, int *width, int *height ){
	int w, h;
	ddsPF_t pf;


	/* dummy check */
	if ( buffer == NULL || size <= 0 || pixels == NULL || width == NULL || height == NULL ) {
		return;
	}

	/* null out */
	*pixels = 0;
	*width = 0;
	*height = 0;

	/* get dds info */
	if ( DDSGetInfo( (ddsBuffer_t*) buffer, &w, &h, &pf ) ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Invalid DDS texture\n" );
		return;
	}

	/* only certain types of dds textures are supported */
	if ( pf != DDS_PF_ARGB8888 && pf != DDS_PF_DXT1 && pf != DDS_PF_DXT3 && pf != DDS_PF_DXT5 ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Only DDS texture formats ARGB8888, DXT1, DXT3, and DXT5 are supported (%d)\n", pf );
		return;
	}

	/* create image pixel buffer */
	*width = w;
	*height = h;
	*pixels = safe_malloc( w * h * 4 );

	/* decompress the dds texture */
	DDSDecompress( (ddsBuffer_t*) buffer, *pixels );
}