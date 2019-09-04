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
typedef  int /*<<< orphan*/  uv_loop_t ;
struct test_thread {int thread_called; } ;
struct getaddrinfo_req {int counter; int /*<<< orphan*/ * loop; } ;
struct fs_req {int counter; int /*<<< orphan*/ * loop; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct getaddrinfo_req*) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  fs_do (struct getaddrinfo_req*) ; 
 int /*<<< orphan*/  getaddrinfo_do (struct getaddrinfo_req*) ; 
 scalar_t__ uv_loop_close (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_loop_init (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_work(void* arg) {
  struct getaddrinfo_req getaddrinfo_reqs[4];
  struct fs_req fs_reqs[4];
  uv_loop_t loop;
  size_t i;
  struct test_thread* thread = arg;

  ASSERT(0 == uv_loop_init(&loop));

  for (i = 0; i < ARRAY_SIZE(getaddrinfo_reqs); i++) {
    struct getaddrinfo_req* req = getaddrinfo_reqs + i;
    req->counter = 4;
    req->loop = &loop;
    getaddrinfo_do(req);
  }

  for (i = 0; i < ARRAY_SIZE(fs_reqs); i++) {
    struct fs_req* req = fs_reqs + i;
    req->counter = 4;
    req->loop = &loop;
    fs_do(req);
  }

  ASSERT(0 == uv_run(&loop, UV_RUN_DEFAULT));
  ASSERT(0 == uv_loop_close(&loop));
  thread->thread_called = 1;
}