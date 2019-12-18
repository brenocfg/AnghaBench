#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__ const* workspace; } ;
struct TYPE_5__ {int /*<<< orphan*/  localDict; TYPE_4__ workspace; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_cwksp_sizeof (TYPE_4__*) ; 
 size_t ZSTD_sizeof_localDict (int /*<<< orphan*/ ) ; 
 size_t ZSTD_sizeof_mtctx (TYPE_1__ const*) ; 

size_t ZSTD_sizeof_CCtx(const ZSTD_CCtx* cctx)
{
    if (cctx==NULL) return 0;   /* support sizeof on NULL */
    /* cctx may be in the workspace */
    return (cctx->workspace.workspace == cctx ? 0 : sizeof(*cctx))
           + ZSTD_cwksp_sizeof(&cctx->workspace)
           + ZSTD_sizeof_localDict(cctx->localDict)
           + ZSTD_sizeof_mtctx(cctx);
}