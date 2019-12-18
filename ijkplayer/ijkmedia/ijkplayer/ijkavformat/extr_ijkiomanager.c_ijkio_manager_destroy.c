#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fd; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cache_file_path; scalar_t__ threadpool_ctx; int /*<<< orphan*/ * cache_info_map; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ijk_ctx_map; TYPE_3__* ijkio_app_ctx; int /*<<< orphan*/  cache_map_path; scalar_t__ auto_save_map; } ;
typedef  TYPE_1__ IjkIOManagerContext ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IJK_IMMEDIATE_SHUTDOWN ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ijk_map_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijk_map_traversal_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijk_threadpool_destroy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijkio_application_closep (TYPE_3__**) ; 
 int /*<<< orphan*/  ijkio_manager_save_tree_to_file ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_destroy ; 

void ijkio_manager_destroy(IjkIOManagerContext *h)
{
    FILE *map_tree_info_fp = NULL;

    if (h->ijkio_app_ctx) {
        if (h->auto_save_map) {
            map_tree_info_fp = fopen(h->cache_map_path, "w");
            if (map_tree_info_fp) {
                ijk_map_traversal_handle(h->ijkio_app_ctx->cache_info_map, map_tree_info_fp, ijkio_manager_save_tree_to_file);
                fclose(map_tree_info_fp);
            }
        }

        ijk_map_traversal_handle(h->ijkio_app_ctx->cache_info_map, NULL, tree_destroy);
        ijk_map_destroy(h->ijkio_app_ctx->cache_info_map);
        h->ijkio_app_ctx->cache_info_map = NULL;

        if (h->ijkio_app_ctx->threadpool_ctx) {
            ijk_threadpool_destroy(h->ijkio_app_ctx->threadpool_ctx, IJK_IMMEDIATE_SHUTDOWN);
        }

        if (0 != strlen(h->ijkio_app_ctx->cache_file_path)) {
            if (h->ijkio_app_ctx->fd >= 0) {
                close(h->ijkio_app_ctx->fd);
            }
        }
        pthread_mutex_destroy(&h->ijkio_app_ctx->mutex);

        ijkio_application_closep(&h->ijkio_app_ctx);
    }

    ijk_map_destroy(h->ijk_ctx_map);
    h->ijk_ctx_map = NULL;

    free(h);
}