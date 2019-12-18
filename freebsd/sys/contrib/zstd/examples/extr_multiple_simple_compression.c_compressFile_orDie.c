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
struct TYPE_3__ {int /*<<< orphan*/  cBuffer; int /*<<< orphan*/  fBuffer; int /*<<< orphan*/  cBufferSize; int /*<<< orphan*/  cctx; int /*<<< orphan*/  fBufferSize; } ;
typedef  TYPE_1__ resources ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ZSTD (size_t const) ; 
 size_t ZSTD_compressCCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 size_t loadFile_orDie (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,unsigned int,unsigned int,char const*) ; 
 int /*<<< orphan*/  saveFile_orDie (char const*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void compressFile_orDie(resources ress, const char* fname, const char* oname)
{
    size_t fSize = loadFile_orDie(fname, ress.fBuffer, ress.fBufferSize);

    /* Compress using the context.
     * If you need more control over parameters, use the advanced API:
     * ZSTD_CCtx_setParameter(), and ZSTD_compress2().
     */
    size_t const cSize = ZSTD_compressCCtx(ress.cctx, ress.cBuffer, ress.cBufferSize, ress.fBuffer, fSize, 1);
    CHECK_ZSTD(cSize);

    saveFile_orDie(oname, ress.cBuffer, cSize);

    /* success */
    printf("%25s : %6u -> %7u - %s \n", fname, (unsigned)fSize, (unsigned)cSize, oname);
}