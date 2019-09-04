#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int binlogs; int /*<<< orphan*/  mutex_write; TYPE_2__** B; } ;
typedef  TYPE_1__ volume_t ;
struct TYPE_8__ {int dir_id; long long volume_id; int binlog_file_id; long long size; int mtime; int fd_rdonly; int fd_wronly; int /*<<< orphan*/  abs_filename; } ;
typedef  TYPE_2__ storage_binlog_file_t ;
struct TYPE_9__ {int path; } ;

/* Variables and functions */
 TYPE_6__* Dirs ; 
 int MAX_VOLUME_BINLOGS ; 
 int PATH_MAX ; 
 int STORAGE_ERR_PATH_TOO_LONG ; 
 int STORAGE_ERR_TOO_MANY_BINLOGS ; 
 TYPE_1__* get_volume_f (long long,int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_volume_info (char const*,long long*,long long*,int*) ; 
 char* realpath (char const*,char*) ; 
 int /*<<< orphan*/  storage_evaluate_priorities (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 TYPE_2__* tszmalloc0 (int) ; 

int storage_add_binlog (const char *binlogname, int dir_id) {
  char real_filename_buf[PATH_MAX];
  char *abs_filename = realpath (binlogname, real_filename_buf);
  if (abs_filename == NULL) {
    kprintf ("absolute filename for binlog %s is too long. %m\n", binlogname);
    return STORAGE_ERR_PATH_TOO_LONG;
  }
  long long volume_id, size;
  int i, mtime;
  int r = read_volume_info (binlogname, &volume_id, &size, &mtime);
  if (r < 0) {
    kprintf ("read_volume_info (%s) return error code %d.\n", binlogname, r);
    return r;
  }
  volume_t *V = get_volume_f (volume_id, 1);
  for (i = 0; i < V->binlogs; i++) {
    if (!strcmp (abs_filename, V->B[i]->abs_filename)) {
      return i;
    }
  }
  if (V->binlogs == MAX_VOLUME_BINLOGS) {
    kprintf ("Found too many binlogs for volume_id = %lld (max binlogs = %d).\n", volume_id, MAX_VOLUME_BINLOGS);
    return STORAGE_ERR_TOO_MANY_BINLOGS;
  }

  for (i = 0; i < V->binlogs; i++) {
    if (V->B[i]->dir_id == dir_id) {
      kprintf ("More than one binlog file for volume_id = %lld in directory %s. Hint: your could change extention from .bin for something else for hiding old binlog files.\n", volume_id, Dirs[dir_id].path);
      return STORAGE_ERR_TOO_MANY_BINLOGS;
    }
  }

  pthread_mutex_lock (&V->mutex_write);
  storage_binlog_file_t *B = tszmalloc0 (sizeof (storage_binlog_file_t));
  V->B[V->binlogs] = B;
  B->volume_id = volume_id;
  B->dir_id = dir_id;
  B->binlog_file_id = dir_id;
  B->binlog_file_id <<= 56;
  B->binlog_file_id |= volume_id;
  B->abs_filename = strdup (abs_filename);
  B->size = size;
  B->mtime = mtime;
  B->fd_rdonly = B->fd_wronly = -1;
  V->binlogs++;
  pthread_mutex_unlock (&V->mutex_write);

  storage_evaluate_priorities (V);
  return V->binlogs - 1;
}