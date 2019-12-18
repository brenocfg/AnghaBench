#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct statfs {double f_bavail; double f_blocks; } ;
struct TYPE_6__ {int last_fail_time; int /*<<< orphan*/  fails; int /*<<< orphan*/  success; int /*<<< orphan*/  sequential_fails; } ;
struct TYPE_5__ {int last_fail_time; int sequential_fails; int success; int fails; } ;
struct TYPE_7__ {char* path; int binlogs; TYPE_2__ st_fsync; TYPE_1__ st_read; scalar_t__ scanned; scalar_t__ disabled; int /*<<< orphan*/  pending_aio_connections; } ;
typedef  TYPE_3__ storage_dir_t ;

/* Variables and functions */
 int sprintf (char*,char*,int,char*,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statfs (char*,struct statfs*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int get_dir_serialized (char *buffer, storage_dir_t *D) {
  struct statfs st;
  statfs (D->path, &st);
  double free_space_percent = (100.0 * st.f_bavail) / st.f_blocks;
  return sprintf (buffer, "a:14:{"
                            "s:4:\"path\";s:%d:\"%s\";"
                            "s:7:\"binlogs\";i:%d;"
                            "s:8:\"disabled\";i:%d;"
                            "s:7:\"scanned\";i:%d;"
                            "s:19:\"read_last_fail_time\";i:%d;"
                            "s:21:\"read_sequential_fails\";i:%d;"
                            "s:12:\"read_success\";d:%lld;"
                            "s:10:\"read_fails\";d:%lld;"
                            "s:20:\"fsync_last_fail_time\";i:%d;"
                            "s:22:\"fsync_sequential_fails\";i:%d;"
                            "s:13:\"fsync_success\";d:%lld;"
                            "s:11:\"fsync_fails\";d:%lld;"
                            "s:18:\"free_space_percent\";d:%.10lf;"
                            "s:23:\"pending_aio_connections\";i:%d;"
                          "}",
   (int) strlen (D->path), D->path,
   D->binlogs,
   (int) D->disabled,
   (int) D->scanned,
   D->st_read.last_fail_time,
   D->st_read.sequential_fails,
   D->st_read.success,
   D->st_read.fails,
   D->st_fsync.last_fail_time,
   D->st_fsync.sequential_fails,
   D->st_fsync.success,
   D->st_fsync.fails,
   free_space_percent,
   D->pending_aio_connections
   );
}