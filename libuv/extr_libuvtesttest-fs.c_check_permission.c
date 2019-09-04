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
struct TYPE_5__ {int st_mode; } ;
typedef  TYPE_1__ uv_stat_t ;
struct TYPE_6__ {scalar_t__ result; TYPE_1__ statbuf; } ;
typedef  TYPE_2__ uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_2__*) ; 
 int uv_fs_stat (int /*<<< orphan*/ *,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_permission(const char* filename, unsigned int mode) {
  int r;
  uv_fs_t req;
  uv_stat_t* s;

  r = uv_fs_stat(NULL, &req, filename, NULL);
  ASSERT(r == 0);
  ASSERT(req.result == 0);

  s = &req.statbuf;
#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MSYS__)
  /*
   * On Windows, chmod can only modify S_IWUSR (_S_IWRITE) bit,
   * so only testing for the specified flags.
   */
  ASSERT((s->st_mode & 0777) & mode);
#else
  ASSERT((s->st_mode & 0777) == mode);
#endif

  uv_fs_req_cleanup(&req);
}