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
typedef  int /*<<< orphan*/  uv_stat_t ;
struct stat {int dummy; } ;

/* Variables and functions */
 int UV_ENOSYS ; 
 int stat (char const*,struct stat*) ; 
 int uv__fs_statx (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__to_stat (struct stat*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__fs_stat(const char *path, uv_stat_t *buf) {
  struct stat pbuf;
  int ret;

  ret = uv__fs_statx(-1, path, /* is_fstat */ 0, /* is_lstat */ 0, buf);
  if (ret != UV_ENOSYS)
    return ret;

  ret = stat(path, &pbuf);
  if (ret == 0)
    uv__to_stat(&pbuf, buf);

  return ret;
}