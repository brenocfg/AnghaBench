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
struct stat {int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mtime; } ;
struct kfs_file_info {int refcnt; char* filename; char* suffix; int flags; long long min_log_pos; long long max_log_pos; int /*<<< orphan*/  kfs_file_type; void* filename_len; int /*<<< orphan*/  device; int /*<<< orphan*/  inode; int /*<<< orphan*/  file_size; int /*<<< orphan*/  mtime; } ;

/* Variables and functions */
 struct kfs_file_info* calloc (int,int) ; 
 int classify_suffix (char*,int,long long*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfs_binlog ; 
 int /*<<< orphan*/  kfs_partial ; 
 int /*<<< orphan*/  kfs_snapshot ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 void* strlen (char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static struct kfs_file_info *kfs_file_info_alloc (const char *filename, int cut_backup_suffix) {
  struct stat st;
  if (stat (filename, &st) < 0) {
    fprintf (stderr, "error: unable to stat %s: %m\n", filename);
    return NULL;
  }

  struct kfs_file_info *FI = calloc (sizeof (*FI), 1);
  if (FI == NULL) {
    return NULL;
  }

  FI->mtime = st.st_mtime;
  FI->file_size = st.st_size;
  FI->inode = st.st_ino;
  FI->device = st.st_dev;
  FI->refcnt = 1;
  FI->filename = strdup (filename);
  FI->filename_len = strlen (filename);

  char *p = strrchr (FI->filename, '/');
  FI->suffix = p ? (p + 1) : FI->filename;
  p = strchr (FI->suffix, '.');
  if (p) {
    FI->suffix = p;
  }

  int l = strlen (FI->suffix);
  if (cut_backup_suffix) {
    if (l > 11 && FI->suffix[l-11] == '.') {
      int i;
      for (i = 1; i <= 10; i++) {
        if (FI->suffix[l-i] < '0' || FI->suffix[l-i] > '9') {
          break;
        }
      }
      if (i > 10) {
        l -= 11;
      }
    }
  }

  long long MMPos[2];
  const char last = FI->suffix[l];
  FI->suffix[l] = 0;
  FI->flags = classify_suffix (FI->suffix, l, MMPos);
  FI->suffix[l] = last;
  FI->min_log_pos = MMPos[0];
  FI->max_log_pos = MMPos[1];
  if (FI->flags >= 0) {
    switch (FI->flags & 3) {
      case 0:
        FI->kfs_file_type = kfs_binlog;
        break;
      case 1:
        FI->kfs_file_type = kfs_snapshot;
        break;
      case 3:
        FI->kfs_file_type = kfs_partial;
        break;
    }
  }
  return FI;
}