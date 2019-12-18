#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread_ctx {int size; char* data; int interval; int /*<<< orphan*/  pid; int /*<<< orphan*/  fd; scalar_t__ doread; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void thread_main(void* arg) {
  const struct thread_ctx* ctx;
  int size;
  char* data;

  ctx = (struct thread_ctx*)arg;
  size = ctx->size;
  data = ctx->data;

  while (size > 0) {
    ssize_t result;
    int nbytes;
    nbytes = size < ctx->interval ? size : ctx->interval;
    if (ctx->doread) {
      result = write(ctx->fd, data, nbytes);
      /* Should not see EINTR (or other errors) */
      ASSERT(result == nbytes);
    } else {
      result = read(ctx->fd, data, nbytes);
      /* Should not see EINTR (or other errors),
       * but might get a partial read if we are faster than the writer
       */
      ASSERT(result > 0 && result <= nbytes);
    }

    pthread_kill(ctx->pid, SIGUSR1);
    size -= result;
    data += result;
  }
}