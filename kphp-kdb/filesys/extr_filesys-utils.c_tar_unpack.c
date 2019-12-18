#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uid_t ;
typedef  void* time_t ;
struct TYPE_4__ {struct tar_unpack_dir_mtime_entry** e; } ;
typedef  TYPE_1__ tar_unpack_dir_mtime_t ;
struct stat {int st_mode; int st_size; void* st_mtime; void* st_atime; void* st_gid; void* st_uid; } ;
struct tar_unpack_dir_mtime_entry {char* dirname; struct stat st; struct tar_unpack_dir_mtime_entry* next; } ;
typedef  int off_t ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  gzFile ;
typedef  void* gid_t ;
typedef  int /*<<< orphan*/  dyn_mark_t ;

/* Variables and functions */
 int MAX_DIR_DEPTH ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int S_ISDIR (int) ; 
 int S_ISLNK (int) ; 
 int TAR_UNPACK_ERR_COPY_ATTRS ; 
 int TAR_UNPACK_ERR_MKDIR ; 
 int TAR_UNPACK_ERR_OPEN ; 
 int TAR_UNPACK_ERR_SYMLINK ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 void* get_oct (char*,int,int) ; 
 scalar_t__ gzclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzdopen (int,char*) ; 
 int gzread (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int lcopy_attrs (char*,struct stat*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int open (char*,int,int) ; 
 int snprintf (char*,int,char*,char const* const,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 
 int /*<<< orphan*/  tar_unpack_check_header (char*) ; 
 int /*<<< orphan*/  tar_unpack_dir_mtime_add (TYPE_1__*,char*,struct stat*) ; 
 int /*<<< orphan*/  tar_unpack_dir_mtime_init (TYPE_1__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*,int,void*,void*,long long,unsigned int,char) ; 
 int write (int,char*,int) ; 
 char* zmalloc (int) ; 

int tar_unpack (int tar_gz_fd, const char *const path) {
  char full_filename[PATH_MAX], long_filename[PATH_MAX];
  int i, res = 0;
  dyn_mark_t mrk;
  dyn_mark (mrk);
  tar_unpack_dir_mtime_t M;
  tar_unpack_dir_mtime_init (&M);
  gzFile f = gzdopen (tar_gz_fd, "rb");
  char buf[512];
  int BUF_SIZE = 16 << 20;
  char *io_buff = zmalloc (BUF_SIZE);
  assert (io_buff != NULL);
  int headers = 0;
  while (gzread (f, buf, 512) == 512) {
    int longlink = 0, longname = 0;
    headers++;
    if (!tar_unpack_check_header (buf)) {
      break;
    }
    char tp = buf[156];
    off_t size = get_oct (buf, 124, 11);
    while (tp == 'K' || tp == 'L') {
      assert (!memcmp (buf, "././@LongLink", 13));
      int padded = (size + 511) & -512;
      if (tp == 'K') {
        longlink = 1;
        assert (padded == gzread (f, io_buff, padded));
      } else if (tp == 'L') {
        longname = 1;
        assert (padded <= PATH_MAX);
        assert (padded == gzread (f, long_filename, padded));
      }
      assert (gzread (f, buf, 512) == 512);
      tar_unpack_check_header (buf);
      tp = buf[156];
      size = get_oct (buf, 124, 11);
    }

    mode_t mode = get_oct (buf, 100, 7);
    uid_t uid = get_oct (buf, 108, 7);
    gid_t gid = get_oct (buf, 116, 7);
    time_t mtime = get_oct (buf, 136, 11);
    char ch;
    if (!longname) {
      memcpy (long_filename, buf + 345, 512 - 345);
      if (long_filename[0]) {
        strcat (long_filename, "/");
      }
      ch = buf[100];
      buf[100] = 0;
      strcat (long_filename, buf);
      buf[100] = ch;
    }
    assert (snprintf (full_filename, PATH_MAX, "%s/%s", path, long_filename) < PATH_MAX);
    vkprintf (2, "%s %07o %d %d %lld %u %c\n", full_filename, mode, uid, gid, (long long) size, (unsigned) mtime, tp);
    struct stat st;
    st.st_mode = mode;
    st.st_uid = uid;
    st.st_gid = gid;
    st.st_size = size;
    st.st_atime = st.st_mtime = mtime;
    int l = strlen (full_filename);
    off_t k = 0;
    int fd = -1;
    switch (tp) {
      case '0':
        k = 0;
        fd = open (full_filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, mode);
        if (fd < 0) {
          kprintf ("open (%s) failed. %m\n", full_filename);
          res = TAR_UNPACK_ERR_OPEN;
          goto exit;
        }
        while (k < size) {
          int o = size - k;
          if (o > BUF_SIZE) { o = BUF_SIZE; }
          int padded = (o + 511) & -512;
          assert (padded == gzread (f, io_buff, padded));
          assert (write (fd, io_buff, o) == o);
          k += padded;
        }
        assert (!close (fd));
        if (lcopy_attrs (full_filename, &st) < 0) {
          res = TAR_UNPACK_ERR_COPY_ATTRS;
          goto exit;
        }
        break;
      case '2':
        assert (S_ISLNK (mode));
        ch = buf[257];
        buf[257] = 0;
        char *oldpath = longlink ? io_buff : buf + 157;
        if (symlink (oldpath, full_filename)) {
          kprintf ("symlink (%s, %s) fail. %m\n", oldpath, full_filename);
          res = TAR_UNPACK_ERR_SYMLINK;
          goto exit;
        }
        buf[257] = ch;
        break;
      case '5':
        assert (S_ISDIR (mode));
        assert (l > 0 && full_filename[l-1] == '/');
        full_filename[l-1] = 0;
        long_filename[strlen (long_filename) - 1] = 0;
        if (mkdir (full_filename, mode)) {
          kprintf ("mkdir (%s, %07o) fail. %m\n", full_filename, mode);
          res = TAR_UNPACK_ERR_MKDIR;
          goto exit;
        }
        tar_unpack_dir_mtime_add (&M, long_filename, &st);
        break;
      default:
        kprintf ("unimplemented file type %c\n", tp);
        assert (0);
        break;
    }
  }

  exit:
  assert (gzclose (f) == Z_OK);
  if (!res) {
    for (i = MAX_DIR_DEPTH - 1; i >= 0; i--) {
      struct tar_unpack_dir_mtime_entry *p;
      for (p = M.e[i]; p != NULL; p = p->next) {
        assert (snprintf (full_filename, PATH_MAX, "%s/%s", path, p->dirname) < PATH_MAX);
        int r = lcopy_attrs (full_filename, &p->st);
        if (r < 0) {
          kprintf ("lcopy_attrs (%s) returns error code %d. %m\n", full_filename, r);
          res = -2;
          goto exit2;
        }
      }
    }
  }
  exit2:

  dyn_release (mrk);
  return res;
}