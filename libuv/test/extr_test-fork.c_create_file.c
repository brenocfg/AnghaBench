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
typedef  int uv_file ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int uv_fs_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int uv_fs_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_file(const char* name) {
  int r;
  uv_file file;
  uv_fs_t req;

  r = uv_fs_open(NULL, &req, name, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR, NULL);
  ASSERT(r >= 0);
  file = r;
  uv_fs_req_cleanup(&req);
  r = uv_fs_close(NULL, &req, file, NULL);
  ASSERT(r == 0);
  uv_fs_req_cleanup(&req);
}