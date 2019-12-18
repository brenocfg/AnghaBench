#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_thread_t ;
struct TYPE_3__ {int flags; size_t stack_size; } ;
typedef  TYPE_1__ uv_thread_options_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 size_t PTHREAD_STACK_MIN ; 
 int UV_THREAD_HAS_STACK_SIZE ; 
 int UV__ERR (int) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ getpagesize () ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setstacksize (int /*<<< orphan*/ *,size_t) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 size_t thread_stack_size () ; 

int uv_thread_create_ex(uv_thread_t* tid,
                        const uv_thread_options_t* params,
                        void (*entry)(void *arg),
                        void *arg) {
  int err;
  pthread_attr_t* attr;
  pthread_attr_t attr_storage;
  size_t pagesize;
  size_t stack_size;

  /* Used to squelch a -Wcast-function-type warning. */
  union {
    void (*in)(void*);
    void* (*out)(void*);
  } f;

  stack_size =
      params->flags & UV_THREAD_HAS_STACK_SIZE ? params->stack_size : 0;

  attr = NULL;
  if (stack_size == 0) {
    stack_size = thread_stack_size();
  } else {
    pagesize = (size_t)getpagesize();
    /* Round up to the nearest page boundary. */
    stack_size = (stack_size + pagesize - 1) &~ (pagesize - 1);
#ifdef PTHREAD_STACK_MIN
    if (stack_size < PTHREAD_STACK_MIN)
      stack_size = PTHREAD_STACK_MIN;
#endif
  }

  if (stack_size > 0) {
    attr = &attr_storage;

    if (pthread_attr_init(attr))
      abort();

    if (pthread_attr_setstacksize(attr, stack_size))
      abort();
  }

  f.in = entry;
  err = pthread_create(tid, attr, f.out, arg);

  if (attr != NULL)
    pthread_attr_destroy(attr);

  return UV__ERR(err);
}