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
struct fuse_file_info {int fh; } ;
struct connection {int /*<<< orphan*/  Tmp; int /*<<< orphan*/  In; } ;
typedef  int /*<<< orphan*/  size ;
typedef  int inode_id_t ;

/* Variables and functions */
 int MAX_VALUE_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmd_set ; 
 int ff_chmod (int*,int) ; 
 int ff_chown (int*,int,int) ; 
 int ff_mkdir (int*,int) ; 
 int ff_rmdir (int*) ; 
 int ff_unlink (int*) ; 
 int ff_write (int /*<<< orphan*/ *,int*,int,unsigned int,struct fuse_file_info*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  init_tmp_buffers (struct connection*) ; 
 int mct_set ; 
 int read_in (int /*<<< orphan*/ *,int*,int) ; 
 int sscanf (char const*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int* value_buff ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ ,int*,int) ; 

int memcache_store (struct connection *c, int op, const char *key, int key_len, int flags, int delay, int size) {
  cmd_set++;
  inode_id_t inode;
  unsigned int offset = 0;
  int act = 0;
  int x = 0, y = 0;
  struct fuse_file_info fi;
  if (size < MAX_VALUE_LEN && key_len > 0 && op == mct_set) {
    switch (*key) {
      case 'c':
        if (!strncmp (key, "chmod", 5) && sscanf (key, "chmod%d", &x) >= 1) {
          act = 6;
        }
        if (!strncmp (key, "chown", 5) && sscanf (key, "chown%d,%d", &x, &y) >= 2) {
          act = 7;
        }
        break;
      case 'm':
        if (!strncmp (key, "mkdir", 5) && sscanf (key, "mkdir%d", &x) >= 1) {
          act = 1;
        }
        break;
      case 'p':
        if (!strcmp (key, "path")) {
          act = 3;
        }
      case 'r':
        if (!strcmp (key, "rmdir")) {
          act = 4;
        }
      case 'w':
        if (sscanf (key, "write%u,%lld", &offset, &inode) >= 2) {
          act = 2;
        }
        break;
      case 'u':
        if (!strcmp (key, "unlink")) {
          act = 5;
        }
    }
    int r = -11;
    if (act) {
      assert (read_in (&c->In, value_buff, size) == size);
      value_buff[size] = 0;
      switch (act) {
        case 1:
          r = ff_mkdir (value_buff, x);
          break;
        case 2:
          fi.fh = inode;
          r = ff_write (NULL, value_buff, size, offset, &fi);
          if (r >= 0) {
            r = 0;
          }
          break;
        case 3:
          init_tmp_buffers (c);
          write_out (c->Tmp, &size, sizeof (size));
          write_out (c->Tmp, value_buff, size);
          r = 0;
          break;
        case 4:
          r = ff_rmdir (value_buff);
          break;
        case 5:
          r = ff_unlink (value_buff);
          break;
        case 6:
          r = ff_chmod (value_buff, x);
          break;
        case 7:
          r = ff_chown (value_buff, x, y);
          break;
      }
      if (!r) {
        return 1;
      }
      if (verbosity > 0 && r < 0) {
        fprintf (stderr, "store: fail (act = %d, res = %d)\n", act, r);
      }
      return 0;
    }
  }
  return -2;
}