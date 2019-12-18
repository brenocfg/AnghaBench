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
struct g_uzip_zstd {int /*<<< orphan*/  guz_dctx; } ;
struct g_uzip_dapi {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 size_t ZSTD_DCtx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ZSTD_getErrorName (size_t) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  ZSTD_reset_session_and_parameters ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 struct g_uzip_zstd* to_zstd_softc (struct g_uzip_dapi*) ; 

__attribute__((used)) static int
guz_zstd_rewind(struct g_uzip_dapi *zpp, const char *gp_name)
{
	struct g_uzip_zstd *sc;
	size_t rc;

	sc = to_zstd_softc(zpp);
	rc = ZSTD_DCtx_reset(sc->guz_dctx, ZSTD_reset_session_and_parameters);
	if (ZSTD_isError(rc)) {
		printf("%s: UZIP(zstd) rewind failed: %s\n", gp_name,
		    ZSTD_getErrorName(rc));
		return (EIO);
	}
	return (0);
}