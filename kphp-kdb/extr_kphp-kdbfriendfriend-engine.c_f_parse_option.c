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
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binlog_disabled ; 
 long long dynamic_data_buffer_size ; 
 int /*<<< orphan*/  ignored_delete_user_id ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  optarg ; 
 int reverse_friends_mode ; 
 int sscanf (int /*<<< orphan*/ ,char*,...) ; 
 int w_split_mod ; 
 int w_split_rem ; 

int f_parse_option (int val) {
  long long x;
  char c;
  switch (val) {
  case 'I':
    ignored_delete_user_id = atoi(optarg);
    break;
  case 'W':
    assert (sscanf(optarg, "%d,%d", &w_split_rem, &w_split_mod) == 2);
    assert (w_split_mod > 0 && w_split_mod <= 10000 && w_split_rem >= 0 && w_split_rem < w_split_mod);
    break;
  case 'A':
    reverse_friends_mode = 1;
    binlog_disabled ++;
    break;
  case 'H':
    c = 0;
    assert (sscanf (optarg, "%lld%c", &x, &c) >= 1);
    switch (c | 0x20) {
      case 'k':  x <<= 10; break;
      case 'm':  x <<= 20; break;
      case 'g':  x <<= 30; break;
      case 't':  x <<= 40; break;
      default: assert (c == 0x20);
    }
    if (val == 'H' && x >= (1LL << 20) && x <= (sizeof(long) == 4 ? (3LL << 30) : (100LL << 30))) {
      dynamic_data_buffer_size = x;
    }
    break;
  case 'i':
    index_mode ++;
    break;
  default:
    return -1;
  }
  return 0;
}