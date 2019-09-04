#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  gzFile ;
struct TYPE_6__ {char const* const filename; struct stat st; struct TYPE_6__* next; } ;
typedef  TYPE_1__ file_t ;
typedef  int /*<<< orphan*/  dyn_mark_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int TAR_PACK_ERR_FILL_HEADER ; 
 int TAR_PACK_ERR_GZWRITE ; 
 int TAR_PACK_ERR_OPEN ; 
 int TAR_PACK_ERR_PATH_TOO_LONG ; 
 int TAR_PACK_ERR_WRITE_HEADER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_filelist (TYPE_1__*) ; 
 int getdir (char*,TYPE_1__**,int,int) ; 
 int gzwrite (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int readlink (char*,char*,int) ; 
 TYPE_1__* remove_file_from_list (TYPE_1__*,char*) ; 
 int snprintf (char*,int,char*,char const* const,...) ; 
 scalar_t__ tar_fill_header (int /*<<< orphan*/ ,char*,struct stat*,char const* const) ; 
 int /*<<< orphan*/  tar_fill_longlink_header (char*,int,char) ; 
 scalar_t__ tar_write_header (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const* const) ; 
 char* zmalloc (int) ; 

__attribute__((used)) static int rec_tar_pack (gzFile f, const char *const src_path, const char *const path, struct stat *S) {
  vkprintf (3, "rec_tar_pack (path = %s)\n", path);
  char a[PATH_MAX], b[PATH_MAX], header[512];
  if (S_ISLNK (S->st_mode)) {
    if (snprintf (a, PATH_MAX, "%s/%s", src_path, path) >= PATH_MAX) {
      return TAR_PACK_ERR_PATH_TOO_LONG;
    }
    int link_length = readlink (a, b, PATH_MAX);
    if (link_length < 0 || link_length >= PATH_MAX) {
      return -4;
    }
    b[link_length] = 0;
    if (link_length > 100) {
      tar_fill_longlink_header (header, link_length, 'K');
      if (tar_write_header (f, header) < 0) {
        return TAR_PACK_ERR_WRITE_HEADER;
      }
      int i;
      for (i = 0; i < link_length + 1; i += 512) {
        int o = link_length + 1 - i;
        if (o > 512) {
          o = 512;
        }
        memset (header, 0, 512);
        memcpy (header, b + i, o);
        if (gzwrite (f, header, 512) != 512) {
          return TAR_PACK_ERR_GZWRITE;
        }
      }
      link_length = 100;
    }
    if (tar_fill_header (f, header, S, path) < 0) {
      return TAR_PACK_ERR_FILL_HEADER;
    }
    memcpy (header + 157, b,  link_length);
    if (tar_write_header (f, header) < 0) {
      return TAR_PACK_ERR_WRITE_HEADER;
    }
  } else if (S_ISDIR (S->st_mode)) {
    if (path[0]) {
      char slash_ended_path[PATH_MAX];
      assert (snprintf (slash_ended_path, PATH_MAX, "%s/", path) < PATH_MAX);
      if (tar_fill_header (f, header, S, slash_ended_path) < 0) {
        return TAR_PACK_ERR_FILL_HEADER;
      }
      if (tar_write_header (f, header) < 0) {
        return TAR_PACK_ERR_WRITE_HEADER;
      }
    }
    if (snprintf (a, PATH_MAX, "%s/%s", src_path, path) >= PATH_MAX) {
      return TAR_PACK_ERR_PATH_TOO_LONG;
    }
    file_t *px, *p;
    int n = getdir (a, &px, 1, 1);
    if (n < 0) {
      return -2;
    }

    if (!path[0]) {
      px = remove_file_from_list (px, ".filesys-xfs-engine.pid");
    }

    for (p = px; p != NULL; p = p->next) {
      if (path[0]) {
        if (snprintf (a, PATH_MAX, "%s/%s", path, p->filename) >= PATH_MAX) {
          return TAR_PACK_ERR_PATH_TOO_LONG;
        }
      } else {
        if (snprintf (a, PATH_MAX, "%s", p->filename) >= PATH_MAX) {
          return TAR_PACK_ERR_PATH_TOO_LONG;
        }
      }
      int r = rec_tar_pack (f, src_path, a, &p->st);
      if (r < 0) {
        return r;
      }
    }
    free_filelist (px);
  } else {
    if (snprintf (a, PATH_MAX, "%s/%s", src_path, path) >= PATH_MAX) {
      return TAR_PACK_ERR_PATH_TOO_LONG;
    }
    if (tar_fill_header (f, header, S, path) < 0) {
      return TAR_PACK_ERR_FILL_HEADER;
    }
    if (tar_write_header (f, header) < 0) {
      return TAR_PACK_ERR_WRITE_HEADER;
    }
    int fd = open (a, O_RDONLY);
    if (fd < 0) {
      return TAR_PACK_ERR_OPEN;
    }
    int BUF_SIZE = 16 << 20;
    dyn_mark_t mrk;
    dyn_mark (mrk);
    char *buf = zmalloc (BUF_SIZE);
    off_t i = 0;
    while (i < S->st_size) {
      int o = S->st_size - i;
      if (o > BUF_SIZE) { o = BUF_SIZE; }
      int padded = (o + 511) & -512;
      assert (o == read (fd, buf, o));
      if (padded != o) {
        memset (buf + o, 0, padded - o);
      }
      if (gzwrite (f, buf, padded) != padded) {
        dyn_release (mrk);
        return TAR_PACK_ERR_GZWRITE;
      }
      i += padded;
    }
    dyn_release (mrk);
    close (fd);
  }
  return 0;
}