#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ijkio_app_ctx; int /*<<< orphan*/  cache_map_path; } ;
struct TYPE_4__ {int shared; scalar_t__ fd; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cache_info_map; } ;
typedef  TYPE_2__ IjkIOManagerContext ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsync (scalar_t__) ; 
 int /*<<< orphan*/  ijk_map_traversal_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijkio_manager_save_tree_to_file ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void ijkio_manager_will_share_cache_map(IjkIOManagerContext *h) {
    av_log(NULL, AV_LOG_INFO, "will share cache\n");
    if (!h || !h->ijkio_app_ctx || !strlen(h->cache_map_path)) {
        return;
    }

    pthread_mutex_lock(&h->ijkio_app_ctx->mutex);
    FILE *map_tree_info_fp = fopen(h->cache_map_path, "w");
    if (!map_tree_info_fp) {
        pthread_mutex_unlock(&h->ijkio_app_ctx->mutex);
        return;
    }
    h->ijkio_app_ctx->shared = 1;
    ijk_map_traversal_handle(h->ijkio_app_ctx->cache_info_map, map_tree_info_fp, ijkio_manager_save_tree_to_file);
    fclose(map_tree_info_fp);
    if (h->ijkio_app_ctx->fd >= 0) {
        fsync(h->ijkio_app_ctx->fd);
    }
    pthread_mutex_unlock(&h->ijkio_app_ctx->mutex);
}