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
typedef  int /*<<< orphan*/  uv_fs_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int NUM_SYNC_REQS ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fmt (double) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sync_stat (int /*<<< orphan*/ *,char const*) ; 
 int uv_hrtime () ; 

__attribute__((used)) static void sync_bench(const char* path) {
  uint64_t before;
  uint64_t after;
  uv_fs_t req;
  int i;

  /* do the sync benchmark */
  before = uv_hrtime();

  for (i = 0; i < NUM_SYNC_REQS; i++)
    sync_stat(&req, path);

  after = uv_hrtime();

  printf("%s stats (sync): %.2fs (%s/s)\n",
         fmt(1.0 * NUM_SYNC_REQS),
         (after - before) / 1e9,
         fmt((1.0 * NUM_SYNC_REQS) / ((after - before) / 1e9)));
  fflush(stdout);
}