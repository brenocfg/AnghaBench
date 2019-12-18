#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {scalar_t__ cache_max_capacity; int /*<<< orphan*/  fd; int /*<<< orphan*/  read_logical_pos; int /*<<< orphan*/  file_logical_pos; scalar_t__ io_eof_reached; scalar_t__ cache_physical_pos; scalar_t__* last_physical_pos; int /*<<< orphan*/  tree_info; scalar_t__ cur_file_no; int /*<<< orphan*/  cache_info_map; TYPE_1__* ijkio_app_ctx; } ;
struct TYPE_8__ {TYPE_2__* ijkio_app_ctx; TYPE_4__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  shared; } ;
typedef  TYPE_3__ IjkURLContext ;
typedef  TYPE_4__ IjkIOCacheContext ;
typedef  int /*<<< orphan*/  IjkCacheTreeInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ FILE_RW_ERROR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ijk_map_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijk_map_put (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijk_map_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ijk_map_traversal_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_destroy ; 

__attribute__((used)) static int64_t ijkio_cache_file_overrang(IjkURLContext *h, int64_t *cur_pos, int size) {
    IjkIOCacheContext *c = h->priv_data;
    av_log(NULL, AV_LOG_WARNING, "ijkio_cache_file_overrang will flush file\n");

    pthread_mutex_lock(&h->ijkio_app_ctx->mutex);

    if (!c->ijkio_app_ctx->shared) {
        ijk_map_remove(c->cache_info_map, (int64_t)c->cur_file_no);
        ijk_map_traversal_handle(c->cache_info_map, NULL, tree_destroy);
        ijk_map_clear(c->cache_info_map);
        memset(c->tree_info, 0, sizeof(IjkCacheTreeInfo));
        ijk_map_put(c->cache_info_map, (int64_t)c->cur_file_no, c->tree_info);
        *c->last_physical_pos    = 0;
        c->cache_physical_pos    = 0;
        c->io_eof_reached        = 0;
        c->file_logical_pos      = c->read_logical_pos;
        *cur_pos = lseek(c->fd, 0, SEEK_SET);
        if (*cur_pos < 0) {
            goto fail;
        }
    } else {
        goto fail;
    }

    pthread_mutex_unlock(&h->ijkio_app_ctx->mutex);
    return c->cache_max_capacity;

fail:
    pthread_mutex_unlock(&h->ijkio_app_ctx->mutex);
    return FILE_RW_ERROR;
}