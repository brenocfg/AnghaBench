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
 int max_uid ; 

__attribute__((used)) static inline int estimate_users_in_range (int min_user_id, int max_user_id) {
  int _min_uid = (min_user_id - log_split_min + log_split_mod - 1) / log_split_mod;
  int _max_uid = ((long long) max_user_id - log_split_min + log_split_mod) / log_split_mod - 1;
  if (_max_uid > max_uid) {
    _max_uid = max_uid;
  }
  if (_min_uid <= 0) {
    _min_uid = 0;
  }
  return _min_uid <= _max_uid ? _max_uid - _min_uid + 1 : 0;
}