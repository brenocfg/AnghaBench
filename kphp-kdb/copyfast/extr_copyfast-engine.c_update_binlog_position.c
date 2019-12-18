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
struct stat {long long st_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  last_binlog_update; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINLOG_BUFFER_FD ; 
 long long BINLOG_POSITION ; 
 int /*<<< orphan*/  LOG_BINLOG_UPDATED ; 
 long long MAX_BINLOG_SIZE ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  get_double_time_since_epoch () ; 
 int /*<<< orphan*/  log_event (int,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  send_friends_binlog_position () ; 
 int /*<<< orphan*/  update_binlog_buffer (long long) ; 
 int /*<<< orphan*/  update_crc64 (long long) ; 

void update_binlog_position (void) {
  struct stat t;
  fstat (BINLOG_BUFFER_FD, &t);
  long long old_binlog_position = BINLOG_POSITION;
  BINLOG_POSITION = t.st_size;
  assert (BINLOG_POSITION < MAX_BINLOG_SIZE);
  if (BINLOG_POSITION != old_binlog_position) {
    log_event (1, LOG_BINLOG_UPDATED, BINLOG_POSITION);
    update_crc64 (old_binlog_position);
    update_binlog_buffer (old_binlog_position);
    STATS->structured.last_binlog_update = get_double_time_since_epoch ();
    send_friends_binlog_position ();
  }
}