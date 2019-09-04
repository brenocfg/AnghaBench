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
struct TYPE_2__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int) ;} ;
typedef  int GLenum ;

/* Variables and functions */
#define  GL_COMPRESSED_RED_RGTC1 146 
#define  GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 145 
#define  GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 144 
#define  GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 143 
#define  GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 142 
#define  GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 141 
#define  GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 140 
#define  GL_COMPRESSED_RGB_S3TC_DXT1_EXT 139 
#define  GL_COMPRESSED_RG_RGTC2 138 
#define  GL_COMPRESSED_SIGNED_RED_RGTC1 137 
#define  GL_COMPRESSED_SIGNED_RG_RGTC2 136 
#define  GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 135 
#define  GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 134 
#define  GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 133 
#define  GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 132 
#define  GL_COMPRESSED_SRGB_S3TC_DXT1_EXT 131 
#define  GL_RGBA16 130 
#define  GL_RGBA8 129 
#define  GL_SRGB8_ALPHA8_EXT 128 
 int /*<<< orphan*/  PRINT_ALL ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int CalculateMipSize(int width, int height, GLenum picFormat)
{
	int numBlocks = ((width + 3) / 4) * ((height + 3) / 4);
	int numPixels = width * height;

	switch (picFormat)
	{
		case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
		case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
		case GL_COMPRESSED_RED_RGTC1:
		case GL_COMPRESSED_SIGNED_RED_RGTC1:
			return numBlocks * 8;

		case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
		case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
		case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
		case GL_COMPRESSED_RG_RGTC2:
		case GL_COMPRESSED_SIGNED_RG_RGTC2:
		case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB:
		case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB:
		case GL_COMPRESSED_RGBA_BPTC_UNORM_ARB:
		case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB:
			return numBlocks * 16;

		case GL_RGBA8:
		case GL_SRGB8_ALPHA8_EXT:
			return numPixels * 4;

		case GL_RGBA16:
			return numPixels * 8;

		default:
			ri.Printf(PRINT_ALL, "Unsupported texture format %08x\n", picFormat);
			return 0;
	}

	return 0;
}