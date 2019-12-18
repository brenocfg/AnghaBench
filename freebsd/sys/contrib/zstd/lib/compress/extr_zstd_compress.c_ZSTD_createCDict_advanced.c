#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictLoadMethod_e ;
typedef  scalar_t__ ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_cwksp ;
struct TYPE_9__ {int /*<<< orphan*/  customFree; int /*<<< orphan*/  customAlloc; } ;
typedef  TYPE_1__ ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
struct TYPE_10__ {scalar_t__ compressionLevel; TYPE_1__ customMem; int /*<<< orphan*/  workspace; } ;
typedef  TYPE_2__ ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 int HUF_WORKSPACE_SIZE ; 
 int ZSTD_cwksp_align (size_t,int) ; 
 size_t ZSTD_cwksp_alloc_size (int) ; 
 int /*<<< orphan*/  ZSTD_cwksp_init (int /*<<< orphan*/ *,void* const,size_t const) ; 
 int /*<<< orphan*/  ZSTD_cwksp_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_cwksp_reserve_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZSTD_dlm_byRef ; 
 int /*<<< orphan*/  ZSTD_free (void* const,TYPE_1__) ; 
 int /*<<< orphan*/  ZSTD_freeCDict (TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTD_initCDict_internal (TYPE_2__*,void const*,size_t,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (int /*<<< orphan*/ ) ; 
 void* ZSTD_malloc (size_t const,TYPE_1__) ; 
 size_t ZSTD_sizeof_matchState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

ZSTD_CDict* ZSTD_createCDict_advanced(const void* dictBuffer, size_t dictSize,
                                      ZSTD_dictLoadMethod_e dictLoadMethod,
                                      ZSTD_dictContentType_e dictContentType,
                                      ZSTD_compressionParameters cParams, ZSTD_customMem customMem)
{
    DEBUGLOG(3, "ZSTD_createCDict_advanced, mode %u", (unsigned)dictContentType);
    if (!customMem.customAlloc ^ !customMem.customFree) return NULL;

    {   size_t const workspaceSize =
            ZSTD_cwksp_alloc_size(sizeof(ZSTD_CDict)) +
            ZSTD_cwksp_alloc_size(HUF_WORKSPACE_SIZE) +
            ZSTD_sizeof_matchState(&cParams, /* forCCtx */ 0) +
            (dictLoadMethod == ZSTD_dlm_byRef ? 0
             : ZSTD_cwksp_alloc_size(ZSTD_cwksp_align(dictSize, sizeof(void*))));
        void* const workspace = ZSTD_malloc(workspaceSize, customMem);
        ZSTD_cwksp ws;
        ZSTD_CDict* cdict;

        if (!workspace) {
            ZSTD_free(workspace, customMem);
            return NULL;
        }

        ZSTD_cwksp_init(&ws, workspace, workspaceSize);

        cdict = (ZSTD_CDict*)ZSTD_cwksp_reserve_object(&ws, sizeof(ZSTD_CDict));
        assert(cdict != NULL);
        ZSTD_cwksp_move(&cdict->workspace, &ws);
        cdict->customMem = customMem;
        cdict->compressionLevel = 0; /* signals advanced API usage */

        if (ZSTD_isError( ZSTD_initCDict_internal(cdict,
                                        dictBuffer, dictSize,
                                        dictLoadMethod, dictContentType,
                                        cParams) )) {
            ZSTD_freeCDict(cdict);
            return NULL;
        }

        return cdict;
    }
}