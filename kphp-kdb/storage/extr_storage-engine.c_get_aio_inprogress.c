#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int aio_fildes; } ;
struct TYPE_6__ {int /*<<< orphan*/  abs_filename; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int aio_error (TYPE_3__*) ; 
 TYPE_3__ aio_fsync_cbp ; 
 int aio_return (TYPE_3__*) ; 
 TYPE_1__* last_fsync_binlog_file ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  update_binlog_fsync_stat (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vkprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int get_aio_inprogress (void) {
  if (aio_fsync_cbp.aio_fildes < 0) {
    return 0;
  }
  int err = aio_error (&aio_fsync_cbp);
  if (err == EINPROGRESS) {
    return 1;
  }
  int res = aio_return (&aio_fsync_cbp);
  if (res < 0) {
    vkprintf (0, "aio_fsync (%s) fails. %s\n", last_fsync_binlog_file->abs_filename, strerror (res));
    update_binlog_fsync_stat (last_fsync_binlog_file, 0);
  } else {
    update_binlog_fsync_stat (last_fsync_binlog_file, 1);
  }
  aio_fsync_cbp.aio_fildes = -1;
  return 0;
}