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
struct TYPE_6__ {int last_fail_time; int sequential_fails; int success; int fails; } ;
struct TYPE_5__ {int /*<<< orphan*/  fails; int /*<<< orphan*/  success; int /*<<< orphan*/  sequential_fails; int /*<<< orphan*/  last_fail_time; } ;
struct TYPE_7__ {scalar_t__ fd_rdonly; scalar_t__ fd_wronly; char* abs_filename; int dir_id; TYPE_2__ st_read; scalar_t__ size; TYPE_1__ st_fsync; } ;
typedef  TYPE_3__ storage_binlog_file_t ;

/* Variables and functions */
 int sprintf (char*,char*,int,int,char*,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int get_binlog_file_serialized (char *buffer, storage_binlog_file_t *B) {
  int mode = 0;
  if (B->fd_rdonly >= 0) { mode |= 1; }
  if (B->fd_wronly >= 0) { mode |= 2; }
  return sprintf (buffer, "a:12:{"
                         "s:4:\"mode\";i:%d;"
                         "s:4:\"path\";s:%d:\"%s\";"
                         "s:6:\"dir_id\";i:%d;"
                         "s:4:\"size\";i:%d;"
                         "s:19:\"read_last_fail_time\";i:%d;"
                         "s:21:\"read_sequential_fails\";i:%d;"
                         "s:12:\"read_success\";d:%lld;"
                         "s:10:\"read_fails\";d:%lld;"
                         "s:20:\"fsync_last_fail_time\";i:%d;"
                         "s:22:\"fsync_sequential_fails\";i:%d;"
                         "s:13:\"fsync_success\";d:%lld;"
                         "s:11:\"fsync_fails\";d:%lld;"
                       "}",
    mode,
    (int) strlen (B->abs_filename), B->abs_filename,
    B->dir_id,
    (int) B->size,
    B->st_read.last_fail_time,
    B->st_read.sequential_fails,
    B->st_read.success,
    B->st_read.fails,
    B->st_fsync.last_fail_time,
    B->st_fsync.sequential_fails,
    B->st_fsync.success,
    B->st_fsync.fails
    );
}