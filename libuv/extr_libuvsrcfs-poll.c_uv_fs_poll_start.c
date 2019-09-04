#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_6__ {struct poll_ctx* poll_ctx; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_fs_poll_t ;
typedef  int /*<<< orphan*/  uv_fs_poll_cb ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct poll_ctx {unsigned int interval; struct poll_ctx* previous; int /*<<< orphan*/  path; int /*<<< orphan*/  fs_req; TYPE_2__ timer_handle; TYPE_1__* parent_handle; int /*<<< orphan*/  start_time; int /*<<< orphan*/  poll_cb; int /*<<< orphan*/ * loop; } ;

/* Variables and functions */
 int UV_ENOMEM ; 
 int /*<<< orphan*/  UV_HANDLE_INTERNAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  poll_cb ; 
 size_t strlen (char const*) ; 
 struct poll_ctx* uv__calloc (int,int) ; 
 int /*<<< orphan*/  uv__free (struct poll_ctx*) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__handle_unref (TYPE_2__*) ; 
 int uv_fs_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_is_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_now (int /*<<< orphan*/ *) ; 
 int uv_timer_init (int /*<<< orphan*/ *,TYPE_2__*) ; 

int uv_fs_poll_start(uv_fs_poll_t* handle,
                     uv_fs_poll_cb cb,
                     const char* path,
                     unsigned int interval) {
  struct poll_ctx* ctx;
  uv_loop_t* loop;
  size_t len;
  int err;

  if (uv_is_active((uv_handle_t*)handle))
    return 0;

  loop = handle->loop;
  len = strlen(path);
  ctx = uv__calloc(1, sizeof(*ctx) + len);

  if (ctx == NULL)
    return UV_ENOMEM;

  ctx->loop = loop;
  ctx->poll_cb = cb;
  ctx->interval = interval ? interval : 1;
  ctx->start_time = uv_now(loop);
  ctx->parent_handle = handle;
  memcpy(ctx->path, path, len + 1);

  err = uv_timer_init(loop, &ctx->timer_handle);
  if (err < 0)
    goto error;

  ctx->timer_handle.flags |= UV_HANDLE_INTERNAL;
  uv__handle_unref(&ctx->timer_handle);

  err = uv_fs_stat(loop, &ctx->fs_req, ctx->path, poll_cb);
  if (err < 0)
    goto error;

  if (handle->poll_ctx != NULL)
    ctx->previous = handle->poll_ctx;
  handle->poll_ctx = ctx;
  uv__handle_start(handle);

  return 0;

error:
  uv__free(ctx);
  return err;
}