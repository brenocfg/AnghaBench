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
struct TYPE_6__ {long long readto_off; long long const orig_file_size; long long const buffsize; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 scalar_t__ PREVSIZE ; 
 scalar_t__ io_buff ; 
 int /*<<< orphan*/  log_error (char*,char*,...) ; 
 int /*<<< orphan*/  reset_max_errors_limit () ; 
 int /*<<< orphan*/  stream_close (TYPE_1__*) ; 
 int /*<<< orphan*/  stream_eof (TYPE_1__*) ; 
 scalar_t__ stream_open (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stream_read_limited (TYPE_1__*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,char*,long long const) ; 

int check_snapshot_is_readable (char *filename) {
  reset_max_errors_limit ();
  stream_t S;
  if (stream_open (&S, 0, filename, 2) < 0) {
    log_error ("fail to open snapshot '%s'", filename);
    return -1;
  }
  while (!stream_eof (&S)) {
    const long long off = S.readto_off;
    const long long remaining_bytes = S.orig_file_size - off;
    size_t s = remaining_bytes < S.buffsize ? remaining_bytes : S.buffsize;
    if (stream_read_limited (&S, io_buff + PREVSIZE, s) < 0) {
      log_error ("reading shapshot '%s' from offset %lld fail.", filename, off);
      stream_close (&S);
      return -1;
    }
    vkprintf (2, "read %lld bytes from snapshot '%s', offset: %lld\n", (long long) s, filename, off);
  }
  stream_close (&S);
  return 0;
}