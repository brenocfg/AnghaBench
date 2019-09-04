#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* kfs_file_handle_t ;
struct TYPE_5__ {TYPE_1__* info; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int RPC_PROXY_INDEX_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ifd ; 
 int jump_log_crc32 ; 
 long long jump_log_pos ; 
 int jump_log_ts ; 
 scalar_t__ open (char*,int,...) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int write (scalar_t__,int*,int) ; 

void load_index (kfs_file_handle_t index, const char *bname) {
  static int t[5];
  if (!index) {
    if (!binlog_disabled) {
      static char buf[1000];
      snprintf (buf, 1000, "%s.000000", bname);
      ifd = open (buf, O_WRONLY | O_TRUNC | O_CREAT, 0660);
      if (ifd < 0) {
        fprintf (stderr, "Error opening index: %m\n");
        exit (1);
      }
      t[0] = RPC_PROXY_INDEX_MAGIC;
      t[1] = 0;
      t[2] = 0;
      t[3] = 0;
      t[4] = 0;
      assert (write (ifd, t, 20) == 20);
    }
    return;
  }
  assert (read (index->fd, t, 20) == 20);
  if (t[0] != RPC_PROXY_INDEX_MAGIC) {
    fprintf (stderr, "Index is not from rpc-proxy\n");
    exit (3);
  }
  jump_log_pos = *(long long *)(t + 1);
  jump_log_crc32 = t[3];
  jump_log_ts = t[4];
  close (index->fd);
  if (!binlog_disabled) {
    ifd = open (index->info->filename, O_WRONLY);
  }
}