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
struct file_info {char* filename; int fd; int flags; char* filepath; int mtime; scalar_t__ fsize; int /*<<< orphan*/  head_data; } ;

/* Variables and functions */
 scalar_t__ BSIZE ; 
 int FIF_DEST ; 
 int FIF_ZIPPED ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int MAX_DIRNAME_LEN ; 
 int MAX_DIR_FILES ; 
 int MAX_FPATH_LEN ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  assert (int) ; 
 struct file_info* dst_files ; 
 int dst_fnum ; 
 char* dstdir ; 
 int /*<<< orphan*/  invalidate_file (struct file_info*) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 scalar_t__ lock_whole_file (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct file_info*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 int time (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct file_info *create_peer (struct file_info *FS) {
  struct file_info *FI = dst_files + dst_fnum;
  int dirname_len = strlen (dstdir), len = strlen (FS->filename);
  int i, utime;

  assert (dst_fnum < MAX_DIR_FILES && dirname_len > 1 && dirname_len < MAX_DIRNAME_LEN);

  memset (FI, 0, sizeof (*FI));

  FI->fd = -1;
  FI->flags = FIF_DEST | (FS->flags & FIF_ZIPPED);

  if (dstdir[dirname_len - 1] == '/') {
    dirname_len--;
  }

  memcpy (FI->filepath, dstdir, dirname_len);
  FI->filepath[dirname_len] = '/';
  FI->filename = FI->filepath + dirname_len + 1;

  memcpy (FI->filepath + dirname_len + 1, FS->filename, len);
  assert (dirname_len + len + 13 < MAX_FPATH_LEN);

  utime = time (0);
  for (i = 0; i < 8; i++) {
    sprintf (FI->filename + len, ".%d", utime + i);
    FI->fd = open (FI->filepath, O_CREAT | O_EXCL | O_RDWR, 0640);
    if (FI->fd >= 0) {
      break;
    }
  }

  if (FI->fd < 0) {
    kprintf ("cannot create file %s: %m\n", FI->filepath);
    return 0;
  }

  FI->mtime = utime;
  assert (lock_whole_file (FI->fd, F_WRLCK) > 0);

  if (write (FI->fd, FS->head_data, BSIZE) < BSIZE) {
    kprintf ("cannot write to %s: %m\n", FI->filepath);
    invalidate_file (FI);
    return 0;
  }

  FI->fsize = BSIZE;
  dst_fnum++;

  return FI;
}