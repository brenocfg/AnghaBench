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
struct g_uzip_lzma {int /*<<< orphan*/ * s; } ;
struct g_uzip_dapi {scalar_t__ pvt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GEOM_UZIP ; 
 int /*<<< orphan*/  free (struct g_uzip_lzma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xz_dec_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_uzip_lzma_free(struct g_uzip_dapi *lzpp)
{
	struct g_uzip_lzma *lzp;

	lzp = (struct g_uzip_lzma *)lzpp->pvt;
	if (lzp->s != NULL) {
		xz_dec_end(lzp->s);
		lzp->s = NULL;
	}

	free(lzp, M_GEOM_UZIP);
}