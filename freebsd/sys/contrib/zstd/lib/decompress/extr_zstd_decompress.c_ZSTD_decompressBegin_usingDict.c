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
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_decompressBegin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_decompress_insertDictionary (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

size_t ZSTD_decompressBegin_usingDict(ZSTD_DCtx* dctx, const void* dict, size_t dictSize)
{
    FORWARD_IF_ERROR( ZSTD_decompressBegin(dctx) );
    if (dict && dictSize)
        RETURN_ERROR_IF(
            ZSTD_isError(ZSTD_decompress_insertDictionary(dctx, dict, dictSize)),
            dictionary_corrupted);
    return 0;
}