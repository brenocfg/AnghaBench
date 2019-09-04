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
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {scalar_t__ cur_ffmpeg_ctx; int /*<<< orphan*/  ijk_ctx_map; } ;
struct TYPE_9__ {scalar_t__ state; TYPE_1__* prot; } ;
struct TYPE_8__ {scalar_t__ (* url_seek ) (TYPE_2__*,scalar_t__,int) ;scalar_t__ (* url_resume ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ IjkIOManagerContext ;

/* Variables and functions */
 int IJKAVSEEK_FORCE ; 
 scalar_t__ IJKURL_PAUSED ; 
 scalar_t__ IJKURL_STARTED ; 
 TYPE_2__* ijk_map_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 scalar_t__ stub2 (TYPE_2__*,scalar_t__,int) ; 

int64_t ijkio_manager_io_seek(IjkIOManagerContext *h, int64_t offset, int whence) {
    int64_t ret = -1;

    if (!h)
        return ret;

    IjkURLContext *inner = ijk_map_get(h->ijk_ctx_map, (int64_t)(intptr_t)h->cur_ffmpeg_ctx);
    if (inner && inner->prot && inner->prot->url_seek) {
        if (inner->state == IJKURL_PAUSED) {
            if (inner->prot->url_resume) {
                ret = (int64_t)inner->prot->url_resume(inner);
                if (ret < 0) {
                    return ret;
                }
            }
            inner->state = IJKURL_STARTED;
        }
        ret = inner->prot->url_seek(inner, offset, whence & ~IJKAVSEEK_FORCE);
    }

    return ret;
}