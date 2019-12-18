#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * cctx; int /*<<< orphan*/  buffOutSize; void* buffOut; int /*<<< orphan*/  buffInSize; void* buffIn; } ;
typedef  TYPE_1__ resources ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CHECK_ZSTD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_CStreamInSize () ; 
 int /*<<< orphan*/  ZSTD_CStreamOutSize () ; 
 int /*<<< orphan*/  ZSTD_c_checksumFlag ; 
 int /*<<< orphan*/  ZSTD_c_compressionLevel ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 void* malloc_orDie (int /*<<< orphan*/ ) ; 

__attribute__((used)) static resources createResources_orDie(int cLevel)
{
    resources ress;
    ress.buffInSize = ZSTD_CStreamInSize();   /* can always read one full block */
    ress.buffOutSize= ZSTD_CStreamOutSize();  /* can always flush a full block */
    ress.buffIn = malloc_orDie(ress.buffInSize);
    ress.buffOut= malloc_orDie(ress.buffOutSize);
    ress.cctx = ZSTD_createCCtx();
    CHECK(ress.cctx != NULL, "ZSTD_createCCtx() failed!");

    /* Set any compression parameters you want here.
     * They will persist for every compression operation.
     * Here we set the compression level, and enable the checksum.
     */
    CHECK_ZSTD( ZSTD_CCtx_setParameter(ress.cctx, ZSTD_c_compressionLevel, cLevel) );
    CHECK_ZSTD( ZSTD_CCtx_setParameter(ress.cctx, ZSTD_c_checksumFlag, 1) );
    return ress;
}