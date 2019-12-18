#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * uv_thread_t ;
struct TYPE_5__ {int flags; size_t stack_size; } ;
typedef  TYPE_1__ uv_thread_options_t ;
struct thread_ctx {void (* entry ) (void*) ;int /*<<< orphan*/ * self; void* arg; } ;
struct TYPE_6__ {scalar_t__ dwPageSize; } ;
typedef  TYPE_2__ SYSTEM_INFO ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_SUSPENDED ; 
#define  EACCES 130 
#define  EAGAIN 129 
#define  EINVAL 128 
 int /*<<< orphan*/  GetNativeSystemInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  ResumeThread (int /*<<< orphan*/ *) ; 
 int UV_EACCES ; 
 int UV_EAGAIN ; 
 int UV_EINVAL ; 
 int UV_EIO ; 
 int UV_ENOMEM ; 
 int UV_THREAD_HAS_STACK_SIZE ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,struct thread_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  uv__free (struct thread_ctx*) ; 
 struct thread_ctx* uv__malloc (int) ; 
 int /*<<< orphan*/  uv__thread_start ; 

int uv_thread_create_ex(uv_thread_t* tid,
                        const uv_thread_options_t* params,
                        void (*entry)(void *arg),
                        void *arg) {
  struct thread_ctx* ctx;
  int err;
  HANDLE thread;
  SYSTEM_INFO sysinfo;
  size_t stack_size;
  size_t pagesize;

  stack_size =
      params->flags & UV_THREAD_HAS_STACK_SIZE ? params->stack_size : 0;

  if (stack_size != 0) {
    GetNativeSystemInfo(&sysinfo);
    pagesize = (size_t)sysinfo.dwPageSize;
    /* Round up to the nearest page boundary. */
    stack_size = (stack_size + pagesize - 1) &~ (pagesize - 1);

    if ((unsigned)stack_size != stack_size)
      return UV_EINVAL;
  }

  ctx = uv__malloc(sizeof(*ctx));
  if (ctx == NULL)
    return UV_ENOMEM;

  ctx->entry = entry;
  ctx->arg = arg;

  /* Create the thread in suspended state so we have a chance to pass
   * its own creation handle to it */
  thread = (HANDLE) _beginthreadex(NULL,
                                   (unsigned)stack_size,
                                   uv__thread_start,
                                   ctx,
                                   CREATE_SUSPENDED,
                                   NULL);
  if (thread == NULL) {
    err = errno;
    uv__free(ctx);
  } else {
    err = 0;
    *tid = thread;
    ctx->self = thread;
    ResumeThread(thread);
  }

  switch (err) {
    case 0:
      return 0;
    case EACCES:
      return UV_EACCES;
    case EAGAIN:
      return UV_EAGAIN;
    case EINVAL:
      return UV_EINVAL;
  }

  return UV_EIO;
}