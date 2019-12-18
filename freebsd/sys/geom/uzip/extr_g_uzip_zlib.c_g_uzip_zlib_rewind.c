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
 scalar_t__ Z_OK ; 
 scalar_t__ inflateReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int
g_uzip_zlib_rewind(struct g_uzip_dapi *zpp, const char *gp_name)
{
	int err;
	struct g_uzip_zlib *zp;

	zp = (struct g_uzip_zlib *)zpp->pvt;

	err = 0;
	if (inflateReset(&zp->zs) != Z_OK) {
		printf("%s: UZIP(zlib) decoder reset failed\n", gp_name);
		err = 1;
	}
	return (err);
}