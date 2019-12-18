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
typedef  int uint64_t ;
struct async_req {char const* path; int* count; int /*<<< orphan*/  fs_req; } ;

/* Variables and functions */
 int MAX_CONCURRENT_REQS ; 
 double NUM_ASYNC_REQS ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fmt (double) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,char*) ; 
 int /*<<< orphan*/  stat_cb ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_fs_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int uv_hrtime () ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void async_bench(const char* path) {
  struct async_req reqs[MAX_CONCURRENT_REQS];
  struct async_req* req;
  uint64_t before;
  uint64_t after;
  int count;
  int i;

  for (i = 1; i <= MAX_CONCURRENT_REQS; i++) {
    count = NUM_ASYNC_REQS;

    for (req = reqs; req < reqs + i; req++) {
      req->path = path;
      req->count = &count;
      uv_fs_stat(uv_default_loop(), &req->fs_req, req->path, stat_cb);
    }

    before = uv_hrtime();
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    after = uv_hrtime();

    printf("%s stats (%d concurrent): %.2fs (%s/s)\n",
           fmt(1.0 * NUM_ASYNC_REQS),
           i,
           (after - before) / 1e9,
           fmt((1.0 * NUM_ASYNC_REQS) / ((after - before) / 1e9)));
    fflush(stdout);
  }
}