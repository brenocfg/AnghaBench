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
struct thread_ctx {int /*<<< orphan*/  fd; int /*<<< orphan*/  barrier; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uv_barrier_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thread_main(void* arg) {
  struct thread_ctx* ctx;
  char buf[4096];
  ssize_t n;

  ctx = arg;
  uv_barrier_wait(&ctx->barrier);

  do
    n = read(ctx->fd, buf, sizeof(buf));
  while (n > 0 || (n == -1 && errno == EINTR));

  ASSERT(n == 0);
}