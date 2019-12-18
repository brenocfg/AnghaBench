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
struct message_short {int dummy; } ;
typedef  int /*<<< orphan*/  message_t ;

/* Variables and functions */
 double* UserMsgBytes ; 
 int* UserMsgCnt ; 
 int* UserMsgDel ; 
 int* UserMsgExtras ; 
 double* UserSearchWords ; 
 int /*<<< orphan*/  assert (int) ; 
 int check_needed_passes (double) ; 
 double dyn_cur ; 
 double dyn_top ; 
 int extra_ints_num ; 
 int max_uid ; 
 int msgs_bytes ; 
 double pass_threshold ; 
 scalar_t__ temp_binlog_directory ; 
 scalar_t__ total_packed_bytes ; 

int estimate_needed_passes (void) {
  double total = 0, max_sw, sum, ratio = msgs_bytes ? (double) total_packed_bytes / msgs_bytes : 1;
  double threshold = (dyn_top - dyn_cur) * (temp_binlog_directory ? 0.5 : 0.8);
  int i = 0, k = 0;
  while (i <= max_uid) {
    k++;
    max_sw = 0;
    for (sum = 0; i <= max_uid && sum + max_sw < threshold; i++) {
      if (max_sw < UserSearchWords[i] * 16.0) {
        max_sw = UserSearchWords[i] * 16.0;
      }
      sum += UserMsgCnt[i] * (sizeof (message_t) + 4 * extra_ints_num + 2.2) + 
      	UserMsgBytes[i] * ratio + UserMsgDel[i] * sizeof (struct message_short) +
      	UserMsgExtras[i] * 4;
    }
    total += sum + max_sw;
  }
  pass_threshold = (k ? total / k : threshold);

  assert (check_needed_passes (threshold) <= k);

  while (check_needed_passes (pass_threshold) > k) {
    pass_threshold *= 1.01;
    assert (pass_threshold <= threshold * 1.1);
  }

  return check_needed_passes (pass_threshold);
}