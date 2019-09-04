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
typedef  int list_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  list_id; } ;

/* Variables and functions */
 TYPE_1__** List ; 
 int MAXINT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ list_id_equal (int /*<<< orphan*/ ,int) ; 
 int lists_prime ; 
 int log_split_min ; 
 int log_split_mod ; 
 scalar_t__ max_lists ; 
 scalar_t__ tot_lists ; 

int conv_list_id (list_id_t list_id) {
#if 1
  #ifdef LISTS_Z
  int t = list_id[0];
  #else
  int t = list_id;
  #endif
  if (t == MAXINT) { 
    return -1; 
  }
  t %= log_split_mod;
  if (t != log_split_min && t != -log_split_min) { 
    return -1; 
  }
# ifdef LISTS64
  int p1 = (int)list_id;
  int p2 = (int)(list_id >> 32);
  int h1 = (p1 * 239 + p2) % lists_prime;
  int h2 = (p1 * 17 + p2) % (lists_prime - 1);
# elif defined (LISTS_Z)
  int h1 = 0, h2 = 0, i;
  for (i = 0; i < list_id_ints; i++) {
    h1 = (h1 * 239 + list_id[i]) % lists_prime;
    h2 = (h2 * 17 + list_id[i] + 239) % (lists_prime - 1);
  }
# else
  int h1 = list_id % lists_prime;
  int h2 = (list_id * 17 + 239) % (lists_prime - 1);
# endif
  if (h1 < 0) {
    h1 += lists_prime;
  }
  if (h2 < 0) {
    h2 += lists_prime - 1;
  }
  ++h2;
  while (List[h1]) {
    if (list_id_equal (List[h1]->list_id, list_id)) {
      return h1;
    }
    h1 += h2;
    if (h1 >= lists_prime) {
      h1 -= lists_prime;
    }
  }
  assert (tot_lists < max_lists);
  return h1;
#else
  int t = list_id % log_split_mod;
  list_id += negative_list_id_offset;
  if (list_id < 0) { return -1; }
  if (t != log_split_min && t != -log_split_min) { return -1; }
  list_id /= log_split_mod;
  if (t < 0 && --list_id < 0) {
    return -1;
  }
  return list_id < max_lists ? list_id : -1;
#endif
}