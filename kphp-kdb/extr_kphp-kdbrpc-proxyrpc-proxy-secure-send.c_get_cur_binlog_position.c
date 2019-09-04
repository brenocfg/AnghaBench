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
struct binlog_pos {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  crc32; scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  log_crc32_complement ; 
 scalar_t__ log_crc32_pos ; 
 scalar_t__ log_cur_pos () ; 
 scalar_t__ log_last_pos () ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  relax_log_crc32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relax_write_log_crc32 () ; 

struct binlog_pos get_cur_binlog_position (int replay) {
  struct binlog_pos t;
  if (replay) {
    relax_log_crc32 (0);
    assert (log_cur_pos () == log_crc32_pos);
  } else {
    relax_write_log_crc32 ();
    assert (log_last_pos () == log_crc32_pos);
  }
  //fprintf (stderr, "replay = %d, log_last_pos = %lld, log_crc32_pos = %lld\n", replay, log_last_pos (), log_crc32_pos);
  t.pos = log_crc32_pos;
  t.crc32 = ~log_crc32_complement;
  t.timestamp = now;
  return t;
}