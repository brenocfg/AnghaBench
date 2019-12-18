#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {int orig_file_size; TYPE_3__* F; } ;
struct TYPE_18__ {TYPE_5__* backups; TYPE_6__ S; TYPE_9__* binlog; } ;
typedef  TYPE_4__ file_t ;
struct TYPE_19__ {char* filename; TYPE_6__ S; int /*<<< orphan*/  status; struct TYPE_19__* next; } ;
typedef  TYPE_5__ backup_file_t ;
struct TYPE_21__ {TYPE_1__* info; } ;
struct TYPE_17__ {TYPE_2__* info; } ;
struct TYPE_16__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  preloaded_bytes; int /*<<< orphan*/  start; } ;
struct TYPE_15__ {int /*<<< orphan*/  filename; } ;
struct TYPE_14__ {scalar_t__ max_errors_limit; scalar_t__ errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* backups_dir ; 
 char* basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_differ ; 
 int /*<<< orphan*/  bs_io_error ; 
 int /*<<< orphan*/  bs_larger ; 
 int /*<<< orphan*/  bs_ok ; 
 int /*<<< orphan*/  bs_same_inode ; 
 int /*<<< orphan*/  find_backups () ; 
 TYPE_5__* get_backup_file_f (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_fatal (char*,long long,...) ; 
 int /*<<< orphan*/  log_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ max_log_errors ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_max_errors_limit () ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 TYPE_11__ stats ; 
 scalar_t__ stream_is_zipped (TYPE_6__*) ; 
 scalar_t__ stream_open (TYPE_6__*,TYPE_9__*,char*,int) ; 
 scalar_t__ stream_same_inode (TYPE_6__*,TYPE_6__*) ; 
 int strlen (char*) ; 
 char* zmalloc (int) ; 

__attribute__((used)) static int file_open (file_t *F) {
  backup_file_t *f;
  reset_max_errors_limit ();
  if (max_log_errors) {
    stats.max_errors_limit = stats.errors + max_log_errors;
    if (stats.max_errors_limit < 0) {
      reset_max_errors_limit ();
    }
  }

  find_backups ();
  /* open backup before openning binlog slice */
  char *p = basename (F->binlog->info->filename);
  F->backups = get_backup_file_f (p, strlen (p), 0);
  for (f = F->backups; f != NULL; f = f->next) {
    int l = strlen (f->filename) + strlen (backups_dir) + 1;
    char *a = zmalloc (l + 1);
    assert (snprintf (a, l + 1, "%s/%s", backups_dir, f->filename) == l);
    if (stream_open (&f->S, 0, a, 1) < 0) {
      f->status |= bs_io_error;
    }
  }

  if (stream_open (&F->S, F->binlog, 0, 0) < 0) {
    log_fatal ("openning binlog file '%s' in read-only mode failed.", F->binlog->info->filename);
    return -1;
  }

  if (F->S.orig_file_size % 4) {
    log_fatal ("size(%lld) of '%s' isn't multiple of 4.", (long long) F->S.orig_file_size, F->S.F->info->filename);
    return -1;
  }

  for (f = F->backups; f != NULL; f = f->next) {
    if (!f->status) {
      if (stream_same_inode (&F->S, &f->S)) {
        log_error ("backup '%s' and binlog '%s' have equal inodes.", f->S.F->info->filename, F->S.F->info->filename);
        f->status |= bs_same_inode;
      }
      if (f->S.orig_file_size > F->S.orig_file_size) {
        f->status |= bs_larger;
      }
      if (f->status == bs_ok && stream_is_zipped (&f->S) && stream_is_zipped (&F->S)) {
        if (f->S.orig_file_size != F->S.orig_file_size) {
          log_warning ("backup '%s' and binlog '%s' have different original file size (%lld and %lld).", f->S.F->info->filename, F->S.F->info->filename, f->S.orig_file_size, F->S.orig_file_size);
          f->status |= bs_differ;
        } else if (f->S.F->info->preloaded_bytes != F->S.F->info->preloaded_bytes) {
          log_warning ("backup '%s' and binlog '%s' have different header size (%d and %d).", f->S.F->info->filename, F->S.F->info->filename, f->S.F->info->preloaded_bytes, F->S.F->info->preloaded_bytes);
          f->status |= bs_differ;
        } else if (memcmp (f->S.F->info->start, F->S.F->info->start, F->S.F->info->preloaded_bytes)) {
          log_warning ("backup '%s' and binlog '%s' have different headers.", f->S.F->info->filename, F->S.F->info->filename);
          f->status |= bs_differ;
        }
      }
    }
  }

  for (f = F->backups; f != NULL; f = f->next) {
    if (f->status != bs_ok) {
      continue;
    }
    backup_file_t *g;
    for (g = f->next; g != NULL; g = g->next) {
      if (g->status == bs_ok && stream_same_inode (&f->S, &g->S)) {
        f->status |= bs_same_inode;
        g->status |= bs_same_inode;
        log_error ("backup '%s' and backup '%s' have equal inodes.", f->S.F->info->filename, g->S.F->info->filename);
      }
    }
  }

  return 0;
}