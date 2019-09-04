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
 int extra_ints_num ; 
 int max_uid ; 
 int msgs_bytes ; 
 scalar_t__ total_packed_bytes ; 

int compute_max_uid (int min_uid, double threshold) {
  double sum = 0, max_sw = 0, ratio = msgs_bytes ?  (double) total_packed_bytes / msgs_bytes : 1;
  int i;
  for (i = min_uid; i <= max_uid && sum + max_sw <= threshold; i++) {
    if (max_sw < UserSearchWords[i] * 16.0) {
      max_sw = UserSearchWords[i] * 16.0;
    }
    sum += UserMsgCnt[i] * (sizeof (message_t) + 4 * extra_ints_num + 2.2) + 
      UserMsgBytes[i] * ratio + UserMsgDel[i] * sizeof (struct message_short) +
      UserMsgExtras[i] * 4;
  }
  return i;
}