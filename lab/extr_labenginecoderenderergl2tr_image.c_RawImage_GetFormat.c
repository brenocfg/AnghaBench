#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
typedef  scalar_t__ imgType_t ;
typedef  int imgFlags_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_12__ {scalar_t__ textureCompression; } ;
struct TYPE_11__ {int textureCompression; } ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int integer; } ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 scalar_t__ GL_COMPRESSED_RGBA_BPTC_UNORM_ARB ; 
 scalar_t__ GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ; 
 scalar_t__ GL_COMPRESSED_RGBA_S3TC_DXT5_EXT ; 
 scalar_t__ GL_COMPRESSED_RG_RGTC2 ; 
 scalar_t__ GL_LUMINANCE ; 
 scalar_t__ GL_LUMINANCE8 ; 
 scalar_t__ GL_LUMINANCE8_ALPHA8 ; 
 scalar_t__ GL_LUMINANCE_ALPHA ; 
 scalar_t__ GL_RGB ; 
 scalar_t__ GL_RGB4_S3TC ; 
 scalar_t__ GL_RGB5 ; 
 scalar_t__ GL_RGB8 ; 
 scalar_t__ GL_RGBA ; 
 scalar_t__ GL_RGBA4 ; 
 scalar_t__ GL_RGBA8 ; 
 int IMGFLAG_NO_COMPRESSION ; 
 scalar_t__ IMGTYPE_NORMAL ; 
 scalar_t__ IMGTYPE_NORMALHEIGHT ; 
 scalar_t__ RawImage_HasAlpha (int /*<<< orphan*/  const*,int) ; 
 int TCR_BPTC ; 
 int TCR_RGTC ; 
 scalar_t__ TC_S3TC ; 
 scalar_t__ TC_S3TC_ARB ; 
 TYPE_6__ glConfig ; 
 TYPE_5__ glRefConfig ; 
 TYPE_4__* r_greyscale ; 
 TYPE_3__* r_monolightmaps ; 
 TYPE_2__* r_parallaxMapping ; 
 TYPE_1__* r_texturebits ; 

__attribute__((used)) static GLenum RawImage_GetFormat(const byte *data, int numPixels, GLenum picFormat, qboolean lightMap, imgType_t type, imgFlags_t flags)
{
	int samples = 3;
	GLenum internalFormat = GL_RGB;
	qboolean forceNoCompression = (flags & IMGFLAG_NO_COMPRESSION);
	qboolean normalmap = (type == IMGTYPE_NORMAL || type == IMGTYPE_NORMALHEIGHT);

	if (picFormat != GL_RGBA8)
		return picFormat;

	if(normalmap)
	{
		if ((type == IMGTYPE_NORMALHEIGHT) && RawImage_HasAlpha(data, numPixels) && r_parallaxMapping->integer)
		{
			if (!forceNoCompression && glRefConfig.textureCompression & TCR_BPTC)
			{
				internalFormat = GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
			}
			else if (!forceNoCompression && glConfig.textureCompression == TC_S3TC_ARB)
			{
				internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			}
			else if ( r_texturebits->integer == 16 )
			{
				internalFormat = GL_RGBA4;
			}
			else if ( r_texturebits->integer == 32 )
			{
				internalFormat = GL_RGBA8;
			}
			else
			{
				internalFormat = GL_RGBA;
			}
		}
		else
		{
			if (!forceNoCompression && glRefConfig.textureCompression & TCR_RGTC)
			{
				internalFormat = GL_COMPRESSED_RG_RGTC2;
			}
			else if (!forceNoCompression && glRefConfig.textureCompression & TCR_BPTC)
			{
				internalFormat = GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
			}
			else if (!forceNoCompression && glConfig.textureCompression == TC_S3TC_ARB)
			{
				internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			}
			else if (r_texturebits->integer == 16)
			{
				internalFormat = GL_RGB5;
			}
			else if (r_texturebits->integer == 32)
			{
				internalFormat = GL_RGB8;
			}
			else
			{
				internalFormat = GL_RGB;
			}
		}
	}
	else if(lightMap)
	{
		if(r_greyscale->integer || r_monolightmaps->integer)
			internalFormat = GL_LUMINANCE;
		else
			internalFormat = GL_RGBA;
	}
	else
	{
		if (RawImage_HasAlpha(data, numPixels))
		{
			samples = 4;
		}

		// select proper internal format
		if ( samples == 3 )
		{
			if(r_greyscale->integer)
			{
				if(r_texturebits->integer == 16 || r_texturebits->integer == 32)
					internalFormat = GL_LUMINANCE8;
				else
					internalFormat = GL_LUMINANCE;
			}
			else
			{
				if ( !forceNoCompression && (glRefConfig.textureCompression & TCR_BPTC) )
				{
					internalFormat = GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
				}
				else if ( !forceNoCompression && glConfig.textureCompression == TC_S3TC_ARB )
				{
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				}
				else if ( !forceNoCompression && glConfig.textureCompression == TC_S3TC )
				{
					internalFormat = GL_RGB4_S3TC;
				}
				else if ( r_texturebits->integer == 16 )
				{
					internalFormat = GL_RGB5;
				}
				else if ( r_texturebits->integer == 32 )
				{
					internalFormat = GL_RGB8;
				}
				else
				{
					internalFormat = GL_RGB;
				}
			}
		}
		else if ( samples == 4 )
		{
			if(r_greyscale->integer)
			{
				if(r_texturebits->integer == 16 || r_texturebits->integer == 32)
					internalFormat = GL_LUMINANCE8_ALPHA8;
				else
					internalFormat = GL_LUMINANCE_ALPHA;
			}
			else
			{
				if ( !forceNoCompression && (glRefConfig.textureCompression & TCR_BPTC) )
				{
					internalFormat = GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
				}
				else if ( !forceNoCompression && glConfig.textureCompression == TC_S3TC_ARB )
				{
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				}
				else if ( r_texturebits->integer == 16 )
				{
					internalFormat = GL_RGBA4;
				}
				else if ( r_texturebits->integer == 32 )
				{
					internalFormat = GL_RGBA8;
				}
				else
				{
					internalFormat = GL_RGBA;
				}
			}
		}
	}

	return internalFormat;
}