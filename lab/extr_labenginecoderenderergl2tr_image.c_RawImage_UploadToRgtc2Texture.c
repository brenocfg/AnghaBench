#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int /*<<< orphan*/  (* Hunk_FreeTempMemory ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* Hunk_AllocateTempMemory ) (int) ;} ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  CompressMonoBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GL_COMPRESSED_RG_RGTC2 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  qglCompressedTextureSubImage2DEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/ * stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RawImage_UploadToRgtc2Texture(GLuint texture, int miplevel, int x, int y, int width, int height, byte *data)
{
	int wBlocks, hBlocks, iy, ix, size;
	byte *compressedData, *p;

	wBlocks = (width + 3) / 4;
	hBlocks = (height + 3) / 4;
	size = wBlocks * hBlocks * 16;

	p = compressedData = ri.Hunk_AllocateTempMemory(size);
	for (iy = 0; iy < height; iy += 4)
	{
		int oh = MIN(4, height - iy);

		for (ix = 0; ix < width; ix += 4)
		{
			byte workingData[16];
			int component;

			int ow = MIN(4, width - ix);

			for (component = 0; component < 2; component++)
			{
				int ox, oy;

				for (oy = 0; oy < oh; oy++)
					for (ox = 0; ox < ow; ox++)
						workingData[oy * 4 + ox] = data[((iy + oy) * width + ix + ox) * 4 + component];

				// dupe data to fill
				for (oy = 0; oy < 4; oy++)
					for (ox = (oy < oh) ? ow : 0; ox < 4; ox++)
						workingData[oy * 4 + ox] = workingData[(oy % oh) * 4 + ox % ow];

				CompressMonoBlock(p, workingData);
				p += 8;
			}
		}
	}

	// FIXME: Won't work for x/y that aren't multiples of 4.
	qglCompressedTextureSubImage2DEXT(texture, GL_TEXTURE_2D, miplevel, x, y, width, height, GL_COMPRESSED_RG_RGTC2, size, compressedData);

	ri.Hunk_FreeTempMemory(compressedData);
}