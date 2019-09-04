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
 unsigned int MAX_USERS ; 
 scalar_t__ NEGATIVE_USER_OFFSET ; 
 int log_split_min ; 
 int log_split_mod ; 

__attribute__((used)) static int conv_uid (int user_id) {
  int t = user_id % log_split_mod;
  if (!user_id || (t != log_split_min && t != -log_split_min)) {
    return -1;
  }
  user_id /= log_split_mod;
  if (user_id < 0 || t < 0) {
    user_id--;
  }
  user_id += NEGATIVE_USER_OFFSET;
  return (unsigned) user_id < MAX_USERS ? user_id : -1;
}