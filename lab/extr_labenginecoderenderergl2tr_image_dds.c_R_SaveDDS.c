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
struct TYPE_4__ {int headerSize; int height; int width; int always_0x00000020; int caps; int pixelFormatFlags; int rgbBitCount; int rBitMask; int gBitMask; int bBitMask; int aBitMask; int /*<<< orphan*/  caps2; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ddsHeader_t ;
typedef  char byte ;
struct TYPE_5__ {char* (* Malloc ) (int) ;int /*<<< orphan*/  (* Free ) (char*) ;int /*<<< orphan*/  (* FS_WriteFile ) (char const*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  DDSCAPS2_CUBEMAP ; 
 int DDSCAPS_COMPLEX ; 
 int DDSCAPS_REQUIRED ; 
 int DDSPF_ALPHAPIXELS ; 
 int DDSPF_RGB ; 
 int /*<<< orphan*/  _DDSFLAGS_REQUIRED ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ ri ; 
 char* stub1 (int) ; 
 int /*<<< orphan*/  stub2 (char const*,char*,int) ; 
 int /*<<< orphan*/  stub3 (char*) ; 

void R_SaveDDS(const char *filename, byte *pic, int width, int height, int depth)
{
	byte *data;
	ddsHeader_t *ddsHeader;
	int picSize, size;

	if (!depth)
		depth = 1;

	picSize = width * height * depth * 4;
	size = 4 + sizeof(*ddsHeader) + picSize;
	data = ri.Malloc(size);

	data[0] = 'D';
	data[1] = 'D';
	data[2] = 'S';
	data[3] = ' ';

	ddsHeader = (ddsHeader_t *)(data + 4);
	memset(ddsHeader, 0, sizeof(ddsHeader_t));

	ddsHeader->headerSize = 0x7c;
	ddsHeader->flags = _DDSFLAGS_REQUIRED;
	ddsHeader->height = height;
	ddsHeader->width = width;
	ddsHeader->always_0x00000020 = 0x00000020;
	ddsHeader->caps = DDSCAPS_COMPLEX | DDSCAPS_REQUIRED;

	if (depth == 6)
		ddsHeader->caps2 = DDSCAPS2_CUBEMAP;

	ddsHeader->pixelFormatFlags = DDSPF_RGB | DDSPF_ALPHAPIXELS;
	ddsHeader->rgbBitCount = 32;
	ddsHeader->rBitMask = 0x000000ff;
	ddsHeader->gBitMask = 0x0000ff00;
	ddsHeader->bBitMask = 0x00ff0000;
	ddsHeader->aBitMask = 0xff000000;

	Com_Memcpy(data + 4 + sizeof(*ddsHeader), pic, picSize);

	ri.FS_WriteFile(filename, data, size);

	ri.Free(data);
}