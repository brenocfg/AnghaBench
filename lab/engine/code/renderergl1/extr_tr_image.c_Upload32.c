#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  float byte ;
struct TYPE_18__ {int maxTextureSize; scalar_t__ textureCompression; } ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_16__ {int /*<<< orphan*/  integer; } ;
struct TYPE_15__ {float value; scalar_t__ integer; } ;
struct TYPE_14__ {float value; scalar_t__ integer; } ;
struct TYPE_13__ {int integer; } ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_11__ {int integer; } ;
struct TYPE_10__ {unsigned int* (* Hunk_AllocateTempMemory ) (int) ;int /*<<< orphan*/  (* Hunk_FreeTempMemory ) (unsigned int*) ;} ;
typedef  int GLint ;
typedef  int GLenum ;

/* Variables and functions */
 scalar_t__ Com_Clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memcpy (unsigned int*,unsigned int*,int) ; 
 int GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ; 
 int /*<<< orphan*/  GL_CheckErrors () ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int GL_LUMINANCE ; 
 int GL_LUMINANCE8 ; 
 int GL_LUMINANCE8_ALPHA8 ; 
 int GL_LUMINANCE_ALPHA ; 
 int GL_RGB ; 
 int GL_RGB4_S3TC ; 
 int GL_RGB5 ; 
 int GL_RGB8 ; 
 int GL_RGBA ; 
 int GL_RGBA4 ; 
 int GL_RGBA8 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_ANISOTROPY_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 float LERP (float,float,float) ; 
 float LUMA (float,float,float) ; 
 int /*<<< orphan*/  R_BlendOverTexture (float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_LightScaleTexture (unsigned int*,int,int,int) ; 
 int /*<<< orphan*/  R_MipMap (float*,int,int) ; 
 int /*<<< orphan*/  ResampleTexture (unsigned int*,int,int,unsigned int*,int,int) ; 
 scalar_t__ TC_S3TC ; 
 scalar_t__ TC_S3TC_ARB ; 
 TYPE_9__ glConfig ; 
 int /*<<< orphan*/  gl_filter_max ; 
 int /*<<< orphan*/  gl_filter_min ; 
 int /*<<< orphan*/  maxAnisotropy ; 
 int /*<<< orphan*/ * mipBlendColors ; 
 int /*<<< orphan*/  qglTexImage2D (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  qglTexParameterf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_8__* r_colorMipLevels ; 
 TYPE_7__* r_ext_max_anisotropy ; 
 TYPE_6__* r_greyscale ; 
 TYPE_5__* r_monolightmaps ; 
 TYPE_4__* r_picmip ; 
 TYPE_3__* r_roundImagesDown ; 
 TYPE_2__* r_texturebits ; 
 TYPE_1__ ri ; 
 unsigned int* stub1 (int) ; 
 unsigned int* stub2 (int) ; 
 int /*<<< orphan*/  stub3 (unsigned int*) ; 
 int /*<<< orphan*/  stub4 (unsigned int*) ; 
 scalar_t__ textureFilterAnisotropic ; 
 int textureMaxSize ; 

__attribute__((used)) static void Upload32( unsigned *data, 
						  int width, int height, int numMips,
						  qboolean mipmap, 
						  qboolean picmip, 
							qboolean lightMap,
						  qboolean allowCompression,
						  qboolean capMaxSize,
						  int *format, 
						  int *pUploadWidth, int *pUploadHeight, int *pUploadMips )
{
	int			samples;
	unsigned	*scaledBuffer = NULL;
	unsigned	*resampledBuffer = NULL;
	int			scaled_width, scaled_height;
	int			i, c;
	byte		*scan;
	GLenum		internalFormat = GL_RGB;
	float		rMax = 0, gMax = 0, bMax = 0;
	int			texsizex, texsizey;
	int			miplevel = 0;

	//
	// convert to exact power of 2 sizes
	//
	for (scaled_width = 1 ; scaled_width < width ; scaled_width<<=1)
		;
	for (scaled_height = 1 ; scaled_height < height ; scaled_height<<=1)
		;
	if ( r_roundImagesDown->integer && scaled_width > width )
		scaled_width >>= 1;
	if ( r_roundImagesDown->integer && scaled_height > height )
		scaled_height >>= 1;

	if ( scaled_width != width || scaled_height != height ) {
		resampledBuffer = ri.Hunk_AllocateTempMemory( scaled_width * scaled_height * 4 );
		ResampleTexture (data, width, height, resampledBuffer, scaled_width, scaled_height);
		data = resampledBuffer;
		width = scaled_width;
		height = scaled_height;
	}

	if (capMaxSize) {
		texsizex = ( textureMaxSize <= 0 || textureMaxSize > glConfig.maxTextureSize ) ? glConfig.maxTextureSize : textureMaxSize;
		texsizey = texsizex;
	} else {
		texsizex = width;
		texsizey = height;
	}
	//
	// perform optional picmip operation
	//
	if ( picmip ) {
		scaled_width >>= r_picmip->integer;
		scaled_height >>= r_picmip->integer;
	}

	//
	// clamp to minimum size
	//
	if (scaled_width < 1) {
		scaled_width = 1;
	}
	if (scaled_height < 1) {
		scaled_height = 1;
	}

	//
	// clamp to the current upper OpenGL limit
	// scale both axis down equally so we don't have to
	// deal with a half mip resampling
	//
	while ( scaled_width > texsizex
		|| scaled_height > texsizey ) {
		scaled_width >>= 1;
		scaled_height >>= 1;
	}

	scaledBuffer = ri.Hunk_AllocateTempMemory( sizeof( unsigned ) * scaled_width * scaled_height );

	//
	// scan the texture for each channel's max values
	// and verify if the alpha channel is being used or not
	//
	c = width*height;
	scan = ((byte *)data);
	samples = 3;

	if( r_greyscale->integer || ( lightMap && r_monolightmaps->integer ) )
	{
		for ( i = 0; i < c; i++ )
		{
			byte luma = LUMA(scan[i*4], scan[i*4 + 1], scan[i*4 + 2]);
			scan[i*4] = luma;
			scan[i*4 + 1] = luma;
			scan[i*4 + 2] = luma;
		}
	}
	else if( r_greyscale->value || ( lightMap && r_monolightmaps->value ) )
	{
		float scl = r_greyscale->value ? r_greyscale->value : r_monolightmaps->value;
		for ( i = 0; i < c; i++ )
		{
			float luma = LUMA(scan[i*4], scan[i*4 + 1], scan[i*4 + 2]);
			scan[i*4] = LERP(scan[i*4], luma, scl);
			scan[i*4 + 1] = LERP(scan[i*4 + 1], luma, scl);
			scan[i*4 + 2] = LERP(scan[i*4 + 2], luma, scl);
		}
	}

	if(lightMap)
	{
		if(r_greyscale->integer || r_monolightmaps->integer)
			internalFormat = GL_LUMINANCE;
		else
			internalFormat = GL_RGB;
	}
	else
	{
		for ( i = 0; i < c; i++ )
		{
			if ( scan[i*4+0] > rMax )
			{
				rMax = scan[i*4+0];
			}
			if ( scan[i*4+1] > gMax )
			{
				gMax = scan[i*4+1];
			}
			if ( scan[i*4+2] > bMax )
			{
				bMax = scan[i*4+2];
			}
			if ( scan[i*4 + 3] != 255 ) 
			{
				samples = 4;
				break;
			}
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
				if ( allowCompression && glConfig.textureCompression == TC_S3TC_ARB )
				{
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				}
				else if ( allowCompression && glConfig.textureCompression == TC_S3TC )
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
				if ( r_texturebits->integer == 16 )
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

	*pUploadWidth = scaled_width;
	*pUploadHeight = scaled_height;
	*format = internalFormat;
	*pUploadMips = 1;

	// copy or resample data as appropriate for first MIP level
	if ( ( scaled_width == width ) && 
		( scaled_height == height ) ) {
		if (!mipmap)
		{
			qglTexImage2D (GL_TEXTURE_2D, 0, internalFormat, scaled_width, scaled_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			goto done;
		}
		else
		{
			while ( scaled_width > 1 || scaled_height > 1 ) {
				if ( miplevel + 1 >= numMips ) break;  // stop at the last available mip
				qglTexImage2D (GL_TEXTURE_2D, miplevel, internalFormat, scaled_width, scaled_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				data += scaled_width * scaled_height;
				scaled_width /= 2;
				scaled_height /= 2;
				if ( scaled_width < 1 ) {
					scaled_width = 1;
				}
				if ( scaled_height < 1 ) {
					scaled_height = 1;
				}
				++miplevel;
			}
		}
		Com_Memcpy (scaledBuffer, data, scaled_width*scaled_height*4);
	}
	else
	{
		// use the normal mip-mapping function to go down from here
		while ( width > scaled_width || height > scaled_height ) {
			R_MipMap( (byte *)data, width, height );
			width >>= 1;
			height >>= 1;
			if ( width < 1 ) {
				width = 1;
			}
			if ( height < 1 ) {
				height = 1;
			}
		}
		Com_Memcpy( scaledBuffer, data, width * height * 4 );
	}

	R_LightScaleTexture (scaledBuffer, scaled_width, scaled_height, !mipmap );

	qglTexImage2D (GL_TEXTURE_2D, miplevel, internalFormat, scaled_width, scaled_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, scaledBuffer );

	if (mipmap)
	{
		while (scaled_width > 1 || scaled_height > 1)
		{
			R_MipMap( (byte *)scaledBuffer, scaled_width, scaled_height );
			scaled_width >>= 1;
			scaled_height >>= 1;
			if (scaled_width < 1)
				scaled_width = 1;
			if (scaled_height < 1)
				scaled_height = 1;
			miplevel++;

			if ( r_colorMipLevels->integer ) {
				R_BlendOverTexture( (byte *)scaledBuffer, scaled_width * scaled_height, mipBlendColors[miplevel] );
			}

			qglTexImage2D (GL_TEXTURE_2D, miplevel, internalFormat, scaled_width, scaled_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, scaledBuffer );
		}
		*pUploadMips = miplevel + 1;
	}
done:

	if (mipmap)
	{
		if ( textureFilterAnisotropic )
			qglTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
					(GLint)Com_Clamp( 1, maxAnisotropy, r_ext_max_anisotropy->integer ) );

		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter_min);
		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter_max);
	}
	else
	{
		if ( textureFilterAnisotropic )
			qglTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1 );

		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}

	GL_CheckErrors();

	if ( scaledBuffer != 0 )
		ri.Hunk_FreeTempMemory( scaledBuffer );
	if ( resampledBuffer != 0 )
		ri.Hunk_FreeTempMemory( resampledBuffer );
}