#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct related_binlog {char* path; int flags; int first_file_start_size; scalar_t__ max_binlog_pos; TYPE_2__* binlog; int /*<<< orphan*/  kfs_replica; int /*<<< orphan*/  update_generation; TYPE_1__* local; } ;
struct TYPE_4__ {int flags; char* binlog_tag; } ;
struct TYPE_3__ {size_t location_len; char* location; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  hostname ; 
 size_t hostname_len ; 
 int load_binlog_data (struct related_binlog*) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  open_replica (char*,int) ; 
 int /*<<< orphan*/  sigrtmax_cnt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  valid_binlog_path (char*) ; 
 scalar_t__ workers ; 

int check_binlog (struct related_binlog *R) {
  assert (R && R->local && R->local->location_len > hostname_len && !memcmp (R->local->location, hostname, hostname_len) && R->local->location[hostname_len] == ':');
  char *path = R->path = R->local->location + hostname_len + 1;
  R->flags = R->binlog->flags;
  if (!valid_binlog_path (path)) {
    fprintf (stderr, "local binlog path %s for binlog %s is invalid, ignoring entry\n", path, R->binlog->binlog_tag);
    return -1;
  }
  if (workers) {
    return -1;
  }
  R->kfs_replica = open_replica (path, R->flags & 4 ? 0 : 1);
  R->update_generation = sigrtmax_cnt;
  if (!R->kfs_replica) {
    fprintf (stderr, "error: cannot open kfs replica %s for binlog tag %s, ignoring entry\n", path, R->binlog->binlog_tag);
    return -1;
  }
  R->first_file_start_size = -1;
  R->max_binlog_pos = 0;
  return load_binlog_data (R);
}