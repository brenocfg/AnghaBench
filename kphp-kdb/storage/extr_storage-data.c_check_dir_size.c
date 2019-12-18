#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct statvfs {scalar_t__ f_bavail; scalar_t__ f_bsize; scalar_t__ f_blocks; scalar_t__ f_frsize; } ;
struct TYPE_3__ {int last_statvfs_time; double disk_total_bytes; long long disk_free_bytes; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ storage_dir_t ;

/* Variables and functions */
 int now ; 
 scalar_t__ statvfs (int /*<<< orphan*/ ,struct statvfs*) ; 
 int /*<<< orphan*/  statvfs_calls ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,...) ; 

int check_dir_size (storage_dir_t *D, double max_disk_usage, long long file_size) {
  if (!D->last_statvfs_time ||
       D->last_statvfs_time <= now - 3600 ||
       max_disk_usage * D->disk_total_bytes < (D->disk_total_bytes - D->disk_free_bytes) + file_size + (now - D->last_statvfs_time) * 200000000LL) {
    struct statvfs s;
    if (statvfs (D->path, &s) < 0) {
      vkprintf (2, "statvfs (\"%s\") fail. %m", D->path);
      return 0;
    }
    statvfs_calls++;
    D->last_statvfs_time = now;
    D->disk_total_bytes = (long long) s.f_frsize * (long long) s.f_blocks;
    D->disk_free_bytes = (long long) s.f_bsize * (long long) s.f_bavail;
    vkprintf (4, "path: %s, last_statvfs_time: %d, disk_total_bytes: %lld, disk_free_bytes: %lld\n", D->path, D->last_statvfs_time, D->disk_total_bytes, D->disk_free_bytes);
    return (max_disk_usage * D->disk_total_bytes >= (D->disk_total_bytes - D->disk_free_bytes) + file_size) ? 1 : 0;
  }
  return 1;
}