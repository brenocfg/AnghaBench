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
struct g_uzip_dapi {struct g_uzip_lzma* pvt; int /*<<< orphan*/ * rewind; int /*<<< orphan*/ * free; int /*<<< orphan*/ * decompress; int /*<<< orphan*/  max_blen; } ;
struct g_uzip_lzma {struct g_uzip_dapi pub; int /*<<< orphan*/  blksz; int /*<<< orphan*/ * s; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_compressBound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GEOM_UZIP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  XZ_SINGLE ; 
 int /*<<< orphan*/  free (struct g_uzip_lzma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_uzip_lzma_decompress ; 
 int /*<<< orphan*/  g_uzip_lzma_free ; 
 int /*<<< orphan*/  g_uzip_lzma_nop ; 
 struct g_uzip_lzma* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xz_dec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct g_uzip_dapi *
g_uzip_lzma_ctor(uint32_t blksz)
{
	struct g_uzip_lzma *lzp;

	lzp = malloc(sizeof(struct g_uzip_lzma), M_GEOM_UZIP, M_WAITOK);
	lzp->s = xz_dec_init(XZ_SINGLE, 0);
	if (lzp->s == NULL) {
		goto e1;
	}
	lzp->blksz = blksz;
	lzp->pub.max_blen = LZ4_compressBound(blksz);
	lzp->pub.decompress = &g_uzip_lzma_decompress;
	lzp->pub.free = &g_uzip_lzma_free;
	lzp->pub.rewind = &g_uzip_lzma_nop;
	lzp->pub.pvt = lzp;
	return (&lzp->pub);
e1:
        free(lzp, M_GEOM_UZIP);
        return (NULL);
}