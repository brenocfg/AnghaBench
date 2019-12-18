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
typedef  void ZSTD_CCtx ;

/* Variables and functions */
 int USE_DEFAULT_LEVEL ; 
 size_t ZSTD_CCtx_setParameter (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_c_checksumFlag ; 
 int /*<<< orphan*/  ZSTD_c_compressionLevel ; 
 void* ZSTD_createCCtx () ; 
 int ZSTD_getErrorName (size_t) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int ZSTD_maxCLevel () ; 
 int ZSTD_minCLevel () ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 

void *
mkuz_zstd_init(int *comp_level)
{
	ZSTD_CCtx *cctx;
	size_t rc;

	/* Default chosen for near-parity with mkuzip zlib default. */
	if (*comp_level == USE_DEFAULT_LEVEL)
		*comp_level = 9;
	if (*comp_level < ZSTD_minCLevel() || *comp_level == 0 ||
	    *comp_level > ZSTD_maxCLevel())
		errx(1, "provided compression level %d is invalid",
		    *comp_level);

	cctx = ZSTD_createCCtx();
	if (cctx == NULL)
		errx(1, "could not allocate Zstd context");

	rc = ZSTD_CCtx_setParameter(cctx, ZSTD_c_compressionLevel,
	    *comp_level);
	if (ZSTD_isError(rc))
		errx(1, "Could not set zstd compression level %d: %s",
		    *comp_level, ZSTD_getErrorName(rc));

	rc = ZSTD_CCtx_setParameter(cctx, ZSTD_c_checksumFlag, 1);
	if (ZSTD_isError(rc))
		errx(1, "Could not enable zstd checksum: %s",
		    ZSTD_getErrorName(rc));

	return (cctx);
}