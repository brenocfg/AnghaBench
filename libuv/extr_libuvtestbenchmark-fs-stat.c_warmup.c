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

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int MAX_CONCURRENT_REQS ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  sync_stat (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_fs_req_cleanup ; 
 int /*<<< orphan*/  uv_fs_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void warmup(const char* path) {
  uv_fs_t reqs[MAX_CONCURRENT_REQS];
  unsigned int i;

  /* warm up the thread pool */
  for (i = 0; i < ARRAY_SIZE(reqs); i++)
    uv_fs_stat(uv_default_loop(), reqs + i, path, uv_fs_req_cleanup);

  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  /* warm up the OS dirent cache */
  for (i = 0; i < 16; i++)
    sync_stat(reqs + 0, path);
}