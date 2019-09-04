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

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  after_fork ; 
 int /*<<< orphan*/  before_fork ; 
 int /*<<< orphan*/  child_fork ; 
 int /*<<< orphan*/  global_epoll_lock ; 
 int /*<<< orphan*/  global_epoll_queue ; 
 scalar_t__ pthread_atfork (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void epoll_init(void) {
  QUEUE_INIT(&global_epoll_queue);
  if (uv_mutex_init(&global_epoll_lock))
    abort();

  if (pthread_atfork(&before_fork, &after_fork, &child_fork))
    abort();
}