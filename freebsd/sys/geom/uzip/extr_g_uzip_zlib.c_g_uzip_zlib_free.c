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
struct g_uzip_zlib {int /*<<< orphan*/  zs; } ;
struct g_uzip_dapi {scalar_t__ pvt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GEOM_UZIP ; 
 int /*<<< orphan*/  free (struct g_uzip_zlib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_uzip_zlib_free(struct g_uzip_dapi *zpp)
{
	struct g_uzip_zlib *zp;

	zp = (struct g_uzip_zlib *)zpp->pvt;
	inflateEnd(&zp->zs);
	free(zp, M_GEOM_UZIP);
}