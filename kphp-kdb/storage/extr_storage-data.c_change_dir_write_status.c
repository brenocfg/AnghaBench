#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int disabled; int binlogs; scalar_t__ cur_log_pos; int /*<<< orphan*/  mutex_write; TYPE_3__** B; } ;
typedef  TYPE_1__ volume_t ;
struct stat {scalar_t__ st_size; } ;
struct TYPE_7__ {int disabled; int /*<<< orphan*/  st_fsync; int /*<<< orphan*/  st_read; } ;
typedef  TYPE_2__ storage_dir_t ;
struct TYPE_8__ {int dir_id; int fd_rdonly; int fd_wronly; int /*<<< orphan*/  st_fsync; int /*<<< orphan*/  st_read; int /*<<< orphan*/  abs_filename; } ;
typedef  TYPE_3__ storage_binlog_file_t ;

/* Variables and functions */
 TYPE_2__* Dirs ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 TYPE_1__** Volumes ; 
 int /*<<< orphan*/  close (int) ; 
 int dirs ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 scalar_t__ lock_whole_file (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 
 int volumes ; 

int change_dir_write_status (int dir_id, int disabled) {
  int mask = 1 << dir_id;
  int a = disabled << dir_id;
  int i, j;
  int r = 0;
  if (dir_id < 0 || dir_id >= dirs) {
    return -1;
  }
  storage_dir_t *D = Dirs + dir_id;
  if (D->disabled == disabled) {
    return 0;
  }
  for (i = 0; i < volumes; i++) {
    volume_t *V = Volumes[i];
    storage_binlog_file_t *B = NULL;
    if ((V->disabled & mask) != a) {
      for (j = 0; j < V->binlogs; j++) {
        if (V->B[j]->dir_id == dir_id) {
          B = V->B[j];
          break;
        }
      }
      if (B) {
        V->disabled ^= mask;
        if (disabled) {
          if (B->fd_rdonly >= 0) {
            close (B->fd_rdonly);
            B->fd_rdonly = -1;
          }
          pthread_mutex_lock (&V->mutex_write);
          if (B->fd_wronly >= 0) {
            close (B->fd_wronly);
            B->fd_wronly = -1;
          }
          pthread_mutex_unlock (&V->mutex_write);
        } else {
          if (B->fd_rdonly < 0) {
            int fd = open (B->abs_filename, O_RDONLY);
            if (fd >= 0) {
              B->fd_rdonly = fd;
            }
          }
          pthread_mutex_lock (&V->mutex_write);
          if (B->fd_wronly < 0) {
            int fd = open (B->abs_filename, O_WRONLY);
            if (fd >= 0) {
              struct stat buf;
              if (!fstat (fd, &buf) && buf.st_size == V->cur_log_pos && lock_whole_file (fd, F_WRLCK)) {
                B->fd_wronly = fd;
              } else {
                vkprintf (1, "Didn't open %s in write mode.\n", B->abs_filename);
                close (fd);
              }
            }
          }
          pthread_mutex_unlock (&V->mutex_write);
          memset (&B->st_read, 0, sizeof (B->st_read));
          memset (&B->st_fsync, 0, sizeof (B->st_fsync));
        }
        r++;
      }
    }
  }
  D->disabled = disabled;
  if (!disabled) {
    memset (&D->st_read, 0, sizeof (D->st_read));
    memset (&D->st_fsync, 0, sizeof (D->st_fsync));
  }
  return r;
}