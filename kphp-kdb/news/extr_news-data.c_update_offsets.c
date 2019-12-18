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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_index_mode ; 
 int* days_log_crc32 ; 
 scalar_t__* days_log_offset ; 
 int* days_log_ts ; 
 int last_day ; 
 int log_crc32_complement ; 
 long long log_crc32_pos ; 
 scalar_t__ log_cur_pos () ; 
 int log_last_ts ; 
 size_t next_check_day ; 
 size_t next_check_day_start ; 
 int next_day_start ; 
 int now ; 
 int /*<<< orphan*/  relax_log_crc32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relax_write_log_crc32 () ; 

void update_offsets (int writing_binlog) {
  if (now >= next_day_start) {
    int day = now / 86400;
    int log_ts = log_last_ts;
    if (writing_binlog) {
      relax_write_log_crc32 ();
    } else {
      relax_log_crc32 (0);
    }
    int log_crc32 = ~log_crc32_complement;
    long long log_pos = log_crc32_pos;
    int i;
    for (i = last_day + 1; i <= day; i++) {
      days_log_offset [i] = log_pos;
      days_log_crc32[i] = log_crc32;
      days_log_ts[i] = log_ts;
    }
    last_day = day;
    next_day_start = (last_day + 1) * 86400;
  } else if (check_index_mode) {
    //fprintf (stderr, "%d %d\n", now, next_check_day_start);
    while (days_log_offset[next_check_day] && log_cur_pos () >= days_log_offset[next_check_day]) {
      assert (log_cur_pos () == days_log_offset[next_check_day]);
      relax_log_crc32 (0);
      assert (~log_crc32_complement == days_log_crc32[next_check_day]);
      next_check_day ++;
      next_check_day_start = next_check_day * 86400;
    }
  }
}