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
 int log_split_min ; 
 int log_split_mod ; 

int local_uid (int user_id) {
  user_id %= log_split_mod;
  if (user_id < 0) {
    user_id += log_split_mod;
  }

  if (user_id != log_split_min) {
    return -1;
  }

  return 1;
}