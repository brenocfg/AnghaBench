#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  int /*<<< orphan*/  z_stream ;
struct TYPE_10__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {TYPE_3__ customMem; int /*<<< orphan*/  allocFunc; } ;
typedef  TYPE_2__ ZWRAP_CCtx ;
typedef  TYPE_3__ ZSTD_customMem ;
struct TYPE_8__ {int /*<<< orphan*/  opaque; scalar_t__ (* zalloc ) (int /*<<< orphan*/ ,int,int) ;scalar_t__ zfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZWRAP_allocFunction ; 
 int /*<<< orphan*/  ZWRAP_freeFunction ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ZWRAP_CCtx* ZWRAP_createCCtx(z_streamp strm)
{
    ZWRAP_CCtx* zwc;

    if (strm->zalloc && strm->zfree) {
        zwc = (ZWRAP_CCtx*)strm->zalloc(strm->opaque, 1, sizeof(ZWRAP_CCtx));
        if (zwc==NULL) return NULL;
        memset(zwc, 0, sizeof(ZWRAP_CCtx));
        memcpy(&zwc->allocFunc, strm, sizeof(z_stream));
        {   ZSTD_customMem ZWRAP_customMem = { ZWRAP_allocFunction, ZWRAP_freeFunction, NULL };
            ZWRAP_customMem.opaque = &zwc->allocFunc;
            zwc->customMem = ZWRAP_customMem;
        }
    } else {
        zwc = (ZWRAP_CCtx*)calloc(1, sizeof(*zwc));
        if (zwc==NULL) return NULL;
    }

    return zwc;
}