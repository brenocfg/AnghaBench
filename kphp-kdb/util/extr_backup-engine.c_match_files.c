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
struct file_info {int flags; char* filename; scalar_t__ fsize; int /*<<< orphan*/  filepath; struct file_info* peer; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int FIF_ERROR ; 
 int FIF_RDONLY ; 
 int FIF_ZIPPED ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ all_flags (struct file_info*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ better_match (struct file_info*,struct file_info*) ; 
 struct file_info* create_peer (struct file_info*) ; 
 struct file_info* dst_files ; 
 int dst_fnum ; 
 int /*<<< orphan*/  file_data_free (struct file_info*) ; 
 int /*<<< orphan*/  invalidate_file (struct file_info*) ; 
 int /*<<< orphan*/  kprintf (char*,char*,...) ; 
 scalar_t__ logs_reopen_cnt ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int matches ; 
 int /*<<< orphan*/  memcmp (char*,char*,int const) ; 
 scalar_t__ original_matches_zipped_backup (struct file_info*,struct file_info*) ; 
 scalar_t__ pair_matches (struct file_info*,struct file_info*) ; 
 scalar_t__ remove_useless_not_zipped_backups ; 
 int /*<<< orphan*/  reopen_logs () ; 
 scalar_t__ sigusr1_cnt ; 
 struct file_info* src_files ; 
 int src_fnum ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int match_files (void) {
  struct file_info *FC, *FS, *FD, *FB, *FE;
  int i, j;

  matches = 0;

  for (i = 0, FS = FC = src_files; i < src_fnum; i++, FS++) {

    if (logs_reopen_cnt != sigusr1_cnt) {
      reopen_logs ();
    }

    if (FS->flags & FIF_ERROR) {
      continue;
    }
    FB = FE = NULL;
    for (j = 0, FD = dst_files; j < dst_fnum; j++, FD++) {
      if (FD->flags & FIF_ERROR) {
        continue;
      }

      if (FB == NULL && FE == NULL && all_flags (FD, FIF_ZIPPED | FIF_RDONLY) && !(FS->flags & FIF_ZIPPED) && original_matches_zipped_backup (FS, FD)) {
        FE = FD;
      }

      if (FD->peer) {
        continue;
      }

      if (pair_matches (FS, FD) && (!FB || better_match (FD, FB) > 0)) {
        FB = FD;
      }
    }

    if (FB == NULL) {
      if (FE != NULL) {
        kprintf ("skip creating new uncompressed backup for file '%s', since there is zipped backup '%s'\n", FS->filename, FE->filename);
        continue;
      }
      FB = create_peer (FS);
      if (!FB) {
        kprintf ("warning: unable to create peer for %s\n", FS->filepath);
        continue;
      }
    }
    matches++;
    FS->peer = FB;
    FB->peer = FC;
    assert (lseek (FS->fd, FB->fsize, SEEK_SET) == FB->fsize);
    vkprintf (2, "found peer %s %lld -> %s %lld\n", FS->filepath, FS->fsize, FB->filepath, FB->fsize);
    *FC++ = *FS;
  }

  src_fnum = matches;

  for (j = 0, FD = dst_files; j < dst_fnum; j++, FD++) {
    if (!FD->peer) {
      if (remove_useless_not_zipped_backups && !(FD->flags & FIF_ZIPPED)) {
        for (i = 0, FS = src_files; i < src_fnum; i++, FS++) {
          if (FS->peer && all_flags (FS, FIF_ZIPPED | FIF_RDONLY) && FS->fsize == FS->peer->fsize && all_flags (FS->peer, FIF_ZIPPED | FIF_RDONLY)) {
            char *s2 = FD->filename, *s1 = FS->filename;
            const int l2 = strlen (s2), l1 = strlen (s1);
            if (l2 == l1 - 3 + 11 && !memcmp (s1, s2, l1 - 3) && !strcmp (s1 + l1 - 3, ".bz")) {
              break;
            }
          }
        }
        if (i < src_fnum) {
          kprintf ("unlink useless backup '%s'\n", FD->filepath);
          if (unlink (FD->filepath) < 0) {
            kprintf ("unlink (\"%s\") failed. %m\n", FD->filepath);
          }
        }
      }
      invalidate_file (FD);
    } else {
      file_data_free (FD);
    }
  }

  for (i = 0, FS = src_files; i < src_fnum; i++, FS++) {
    file_data_free (FS);
  }

  return matches;
}