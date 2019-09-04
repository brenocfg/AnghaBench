#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  backup_status_t ;
struct TYPE_9__ {TYPE_6__* F; } ;
struct TYPE_8__ {TYPE_3__ S; } ;
typedef  TYPE_2__ backup_file_t ;
struct TYPE_10__ {TYPE_1__* info; } ;
struct TYPE_7__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 scalar_t__ PREVSIZE ; 
 int /*<<< orphan*/  assert (TYPE_6__*) ; 
 int /*<<< orphan*/  backup_buff ; 
 int /*<<< orphan*/  bs_differ ; 
 int /*<<< orphan*/  bs_io_error ; 
 int /*<<< orphan*/  bs_ok ; 
 scalar_t__ io_buff ; 
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/ ,long long) ; 
 scalar_t__ stream_read_limited (TYPE_3__*,int /*<<< orphan*/ ,long long) ; 
 scalar_t__ stream_seek (TYPE_3__*,long long) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,int /*<<< orphan*/ ,long long) ; 

__attribute__((used)) static int backup_checked_read (backup_file_t *f, long long off, long long s, backup_status_t *status) {
  assert (f->S.F);
  if (stream_seek (&f->S, off) < 0) {
    *status = bs_io_error;
    return -1;
  }
  if (stream_read_limited (&f->S, backup_buff, s) < 0) {
    *status = bs_io_error;
    return -1;
  }

  vkprintf (2, "read %lld bytes from backup '%s', offset: %lld\n", (long long) s, f->S.F->info->filename, off);

  if (memcmp (io_buff + PREVSIZE, backup_buff, s)) {
    *status = bs_differ;
    return -1;
  }
  *status = bs_ok;
  return 0;
}