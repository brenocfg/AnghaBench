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
 int MAX_USERS ; 
 int log_split_min ; 
 int log_split_mod ; 

int conv_user_id (int user_id) {
  if (user_id <= 0) { return -1; }
  if (user_id % log_split_mod != log_split_min) { return -1; }
  user_id /= log_split_mod;
  return user_id < MAX_USERS ? user_id : -1;
}