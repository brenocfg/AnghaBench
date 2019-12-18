#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int* picbyte ;
typedef  int /*<<< orphan*/  new_name ;
typedef  int /*<<< orphan*/  imgType_t ;
typedef  int imgFlags_t ;
struct TYPE_11__ {char* imgName; int flags; struct TYPE_11__* next; } ;
typedef  TYPE_2__ image_t ;
typedef  int byte ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {int* (* Malloc ) (int) ;int /*<<< orphan*/  (* Free ) (int*) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char const*,int,int) ;} ;
struct TYPE_10__ {scalar_t__ (* modify_rgba_texture ) (int /*<<< orphan*/ ,char const*,int*,int,int) ;int /*<<< orphan*/  (* load_texture ) (int /*<<< orphan*/ ,char const*,int**,int*,int*,int* (*) (int)) ;scalar_t__ (* replace_texture_name ) (int /*<<< orphan*/ ,char const*,char*,int) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 int CLAMP (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  COM_StripExtension (char const*,char*,int) ; 
 scalar_t__ GL_RGBA8 ; 
 scalar_t__ GL_SRGB8_ALPHA8_EXT ; 
 int IMGFLAG_CLAMPTOEDGE ; 
 int IMGFLAG_CUBEMAP ; 
 int IMGFLAG_GENNORMALMAP ; 
 int IMGFLAG_MIPMAP ; 
 int IMGFLAG_NOLIGHTSCALE ; 
 int IMGFLAG_PICMIP ; 
 int /*<<< orphan*/  IMGTYPE_COLORALPHA ; 
 int /*<<< orphan*/  IMGTYPE_NORMAL ; 
 int MAX (int,int) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  PRINT_DEVELOPER ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char*) ; 
 int /*<<< orphan*/  RGBAtoNormal (int*,int*,int,int,int) ; 
 int /*<<< orphan*/  RGBAtoYCoCgA (int*,int*,int,int) ; 
 TYPE_2__* R_CreateImage2Internal (char*,int*,int,int,scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_LoadImage (char const*,int**,int*,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  YCoCgAtoRGBA (int*,int*,int,int) ; 
 TYPE_3__* dmlab_context () ; 
 long generateHashValue (char const*) ; 
 TYPE_2__** hashTable ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_5__* r_normalMapping ; 
 TYPE_4__ ri ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*,int,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char const*,int**,int*,int*,int* (*) (int)) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,char const*,int*,int,int) ; 
 int* stub5 (int) ; 
 int* stub6 (int) ; 
 int /*<<< orphan*/  stub7 (int*) ; 
 int /*<<< orphan*/  stub8 (int*) ; 
 int /*<<< orphan*/  stub9 (int*) ; 

image_t	*R_FindImageFile( const char *name, imgType_t type, imgFlags_t flags )
{
	DeepmindContext* ctx = dmlab_context();
	char new_name[MAX_QPATH];
	const char	*file_name = name;
	image_t	*image;
	int		width = 0, height = 0;
	byte	*pic = NULL;
	GLenum  picFormat = GL_RGBA8;
	int picNumMips = 1;
	long	hash;
	imgFlags_t checkFlagsTrue, checkFlagsFalse;
	qboolean capMaxSize = qtrue;

	if (!name) {
		return NULL;
	}

	hash = generateHashValue(name);

	//
	// see if the image is already loaded
	//
	for (image=hashTable[hash]; image; image=image->next) {
		if ( !strcmp( name, image->imgName ) ) {
			// the white image can be used with any set of parms, but other mismatches are errors
			if ( strcmp( name, "*white" ) ) {
				if ( image->flags != flags ) {
					ri.Printf( PRINT_DEVELOPER, "WARNING: reused image %s with mixed flags (%i vs %i)\n", name, image->flags, flags );
				}
			}
			return image;
		}
	}

	if ( ctx->hooks.replace_texture_name( ctx->userdata, name, new_name, sizeof( new_name ) ) ) {
		file_name = new_name;
	}
	//
	// Load the pic from disk or from hooks.
	//
	if ( !ctx->hooks.load_texture( ctx->userdata, file_name, &pic, &width, &height, ri.Malloc ) ) {
		R_LoadImage( file_name, &pic, &width, &height, &picFormat, &picNumMips );
	} else {
		capMaxSize = qfalse;
	}

	if ( pic == NULL ) {
		return NULL;
	}

	// Allow modification of a loaded texture.
	if ( ctx->hooks.modify_rgba_texture( ctx->userdata, name, pic, width, height ) ) {
		capMaxSize = qfalse;
	}

	checkFlagsTrue = IMGFLAG_PICMIP | IMGFLAG_MIPMAP | IMGFLAG_GENNORMALMAP;
	checkFlagsFalse = IMGFLAG_CUBEMAP;
	if (r_normalMapping->integer && (picFormat == GL_RGBA8) && (type == IMGTYPE_COLORALPHA) &&
		((flags & checkFlagsTrue) == checkFlagsTrue) && !(flags & checkFlagsFalse))
	{
		char normalName[MAX_QPATH];
		image_t *normalImage;
		int normalWidth, normalHeight;
		imgFlags_t normalFlags;

		normalFlags = (flags & ~IMGFLAG_GENNORMALMAP) | IMGFLAG_NOLIGHTSCALE;

		COM_StripExtension(name, normalName, MAX_QPATH);
		Q_strcat(normalName, MAX_QPATH, "_n");

		// find normalmap in case it's there
		normalImage = R_FindImageFile(normalName, IMGTYPE_NORMAL, normalFlags);

		// if not, generate it
		if (normalImage == NULL)
		{
			byte *normalPic;
			int x, y;

			normalWidth = width;
			normalHeight = height;
			normalPic = ri.Malloc(width * height * 4);
			RGBAtoNormal(pic, normalPic, width, height, flags & IMGFLAG_CLAMPTOEDGE);

#if 1
			// Brighten up the original image to work with the normal map
			RGBAtoYCoCgA(pic, pic, width, height);
			for (y = 0; y < height; y++)
			{
				byte *picbyte  = pic       + y * width * 4;
				byte *normbyte = normalPic + y * width * 4;
				for (x = 0; x < width; x++)
				{
					int div = MAX(normbyte[2] - 127, 16);
					picbyte[0] = CLAMP(picbyte[0] * 128 / div, 0, 255);
					picbyte  += 4;
					normbyte += 4;
				}
			}
			YCoCgAtoRGBA(pic, pic, width, height);
#else
			// Blur original image's luma to work with the normal map
			{
				byte *blurPic;

				RGBAtoYCoCgA(pic, pic, width, height);
				blurPic = ri.Malloc(width * height);

				for (y = 1; y < height - 1; y++)
				{
					byte *picbyte  = pic     + y * width * 4;
					byte *blurbyte = blurPic + y * width;

					picbyte += 4;
					blurbyte += 1;

					for (x = 1; x < width - 1; x++)
					{
						int result;

						result = *(picbyte - (width + 1) * 4) + *(picbyte - width * 4) + *(picbyte - (width - 1) * 4) +
						         *(picbyte -          1  * 4) + *(picbyte            ) + *(picbyte +          1  * 4) +
						         *(picbyte + (width - 1) * 4) + *(picbyte + width * 4) + *(picbyte + (width + 1) * 4);

						result /= 9;

						*blurbyte = result;
						picbyte += 4;
						blurbyte += 1;
					}
				}

				// FIXME: do borders

				for (y = 1; y < height - 1; y++)
				{
					byte *picbyte  = pic     + y * width * 4;
					byte *blurbyte = blurPic + y * width;

					picbyte += 4;
					blurbyte += 1;

					for (x = 1; x < width - 1; x++)
					{
						picbyte[0] = *blurbyte;
						picbyte += 4;
						blurbyte += 1;
					}
				}

				ri.Free(blurPic);

				YCoCgAtoRGBA(pic, pic, width, height);
			}
#endif

			R_CreateImage2Internal( normalName, normalPic, normalWidth, normalHeight, GL_RGBA8, 0, IMGTYPE_NORMAL, normalFlags, 0, capMaxSize );
			ri.Free( normalPic );
		}
	}

	// force mipmaps off if image is compressed but doesn't have enough mips
	if ((flags & IMGFLAG_MIPMAP) && picFormat != GL_RGBA8 && picFormat != GL_SRGB8_ALPHA8_EXT)
	{
		int wh = MAX(width, height);
		int neededMips = 0;
		while (wh)
		{
			neededMips++;
			wh >>= 1;
		}
		if (neededMips > picNumMips)
			flags &= ~IMGFLAG_MIPMAP;
	}

	image = R_CreateImage2Internal( ( char * ) name, pic, width, height, picFormat, picNumMips, type, flags, 0, capMaxSize );
	ri.Free( pic );
	return image;
}