#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int user_id; } ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
 scalar_t__ MAX_USERS_NUM ; 
 scalar_t__ NEGATIVE_USER_OFFSET ; 
 int USERS_PRIME ; 
 TYPE_1__** User ; 
 int /*<<< orphan*/  assert (int) ; 
 int log_split_min ; 
 int log_split_mod ; 
 scalar_t__ tot_users ; 

int conv_uid (int user_id) {
#if 0
  int t = user_id;
  t %= log_split_mod;
  if (t != log_split_min && t != -log_split_min) {
    return -1;
  }
  int h1 = user_id % USERS_PRIME;
  int h2 = (user_id * 17 + 239) % (USERS_PRIME - 1);
  if (h1 < 0) {
    h1 += USERS_PRIME;
  }
  if (h2 < 0) {
    h2 += USERS_PRIME - 1;
  }
  ++h2;
  while (User[h1]) {
    if (User[h1]->user_id == user_id) {
      return h1;
    }
    h1 += h2;
    if (h1 >= USERS_PRIME) {
      h1 -= USERS_PRIME;
    }
  }
  assert (tot_users < MAX_USERS_NUM);
  return h1;
#else
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
#endif
}