#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_cwksp ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
struct TYPE_4__ {int /*<<< orphan*/  workspace; } ;
typedef  TYPE_1__ const ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int,unsigned int,unsigned int) ; 
 int HUF_WORKSPACE_SIZE ; 
 int ZSTD_cwksp_align (size_t,int) ; 
 size_t const ZSTD_cwksp_alloc_size (int) ; 
 int /*<<< orphan*/  ZSTD_cwksp_init (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  ZSTD_cwksp_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_cwksp_reserve_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZSTD_dlm_byRef ; 
 int /*<<< orphan*/  ZSTD_initCDict_internal (TYPE_1__ const*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (int /*<<< orphan*/ ) ; 
 size_t ZSTD_sizeof_matchState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const ZSTD_CDict* ZSTD_initStaticCDict(
                                 void* workspace, size_t workspaceSize,
                           const void* dict, size_t dictSize,
                                 ZSTD_dictLoadMethod_e dictLoadMethod,
                                 ZSTD_dictContentType_e dictContentType,
                                 ZSTD_compressionParameters cParams)
{
    size_t const matchStateSize = ZSTD_sizeof_matchState(&cParams, /* forCCtx */ 0);
    size_t const neededSize = ZSTD_cwksp_alloc_size(sizeof(ZSTD_CDict))
                            + (dictLoadMethod == ZSTD_dlm_byRef ? 0
                               : ZSTD_cwksp_alloc_size(ZSTD_cwksp_align(dictSize, sizeof(void*))))
                            + ZSTD_cwksp_alloc_size(HUF_WORKSPACE_SIZE)
                            + matchStateSize;
    ZSTD_CDict* cdict;

    if ((size_t)workspace & 7) return NULL;  /* 8-aligned */

    {
        ZSTD_cwksp ws;
        ZSTD_cwksp_init(&ws, workspace, workspaceSize);
        cdict = (ZSTD_CDict*)ZSTD_cwksp_reserve_object(&ws, sizeof(ZSTD_CDict));
        if (cdict == NULL) return NULL;
        ZSTD_cwksp_move(&cdict->workspace, &ws);
    }

    DEBUGLOG(4, "(workspaceSize < neededSize) : (%u < %u) => %u",
        (unsigned)workspaceSize, (unsigned)neededSize, (unsigned)(workspaceSize < neededSize));
    if (workspaceSize < neededSize) return NULL;

    if (ZSTD_isError( ZSTD_initCDict_internal(cdict,
                                              dict, dictSize,
                                              dictLoadMethod, dictContentType,
                                              cParams) ))
        return NULL;

    return cdict;
}