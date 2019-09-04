#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  disk_read_time; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 long long BINLOG_BUFFER ; 
 int /*<<< orphan*/  BINLOG_BUFFER_FD ; 
 long long BINLOG_BUFFER_WPTR ; 
 long long BINLOG_POSITION ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_double_time_since_epoch () ; 
 long long lseek (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,long long,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int get_binlog_data (char *data, long long pos, int len) {
  assert (len > 0);
  assert (pos + len <= BINLOG_POSITION);
  if (verbosity >= 4) {
    fprintf (stderr, "get_binlog_data: pos = %lld, len = %d\n", pos, len);
  }
  if (BINLOG_POSITION - pos + BINLOG_BUFFER <= BINLOG_BUFFER_WPTR) {
    if (verbosity >= 4) {
      fprintf (stderr, "copying from buffer\n");
    }
    memcpy (data, BINLOG_BUFFER_WPTR - (BINLOG_POSITION - pos), len);
  } else {
    if (verbosity >= 4) {
      fprintf (stderr, "reading from file\n");
    }

    STATS->structured.disk_read_time -= get_double_time_since_epoch ();
    assert (lseek (BINLOG_BUFFER_FD, pos, SEEK_SET) == pos);
    assert (read (BINLOG_BUFFER_FD, data, len) == len);
    STATS->structured.disk_read_time += get_double_time_since_epoch ();
  }
  if (verbosity >= 4) {
    fprintf (stderr, "copied data successfully\n");
  }
  return 0;
}