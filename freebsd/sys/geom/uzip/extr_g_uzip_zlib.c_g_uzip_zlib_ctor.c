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
struct g_uzip_dapi {void* pvt; int /*<<< orphan*/ * rewind; int /*<<< orphan*/ * free; int /*<<< orphan*/ * decompress; int /*<<< orphan*/  max_blen; } ;
struct g_uzip_zlib {struct g_uzip_dapi pub; int /*<<< orphan*/  blksz; int /*<<< orphan*/  zs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GEOM_UZIP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  compressBound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct g_uzip_zlib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_uzip_zlib_decompress ; 
 int /*<<< orphan*/  g_uzip_zlib_free ; 
 int /*<<< orphan*/  g_uzip_zlib_rewind ; 
 scalar_t__ inflateInit (int /*<<< orphan*/ *) ; 
 struct g_uzip_zlib* malloc (int,int /*<<< orphan*/ ,int) ; 

struct g_uzip_dapi *
g_uzip_zlib_ctor(uint32_t blksz)
{
	struct g_uzip_zlib *zp;

	zp = malloc(sizeof(struct g_uzip_zlib), M_GEOM_UZIP, M_WAITOK | M_ZERO);
	if (inflateInit(&zp->zs) != Z_OK) {
		goto e1;
	}
	zp->blksz = blksz;
	zp->pub.max_blen = compressBound(blksz);
	zp->pub.decompress = &g_uzip_zlib_decompress;
	zp->pub.free = &g_uzip_zlib_free;
	zp->pub.rewind = &g_uzip_zlib_rewind;
	zp->pub.pvt = (void *)zp;
	return (&zp->pub);
e1:
	free(zp, M_GEOM_UZIP);
	return (NULL);
}