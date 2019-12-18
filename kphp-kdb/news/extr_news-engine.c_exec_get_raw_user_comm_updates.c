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
struct connection {int dummy; } ;

/* Variables and functions */
 int MAX_QUERY ; 
 int* Q ; 
 int QL ; 
 scalar_t__ R ; 
 scalar_t__ R_end ; 
 int /*<<< orphan*/  assert (int) ; 
 int bookmarks_size ; 
 int /*<<< orphan*/  clear_result_buffer () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int get_bookmarks (int,int,int*,int) ; 
 int prepare_raw_comm_updates (int,int,int,int,int) ; 
 int return_one_key_list (struct connection*,char const*,int,int,int,scalar_t__,scalar_t__) ; 
 int sscanf (char const*,char*,int*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int strtol (char const*,char**,int) ; 
 int verbosity ; 

__attribute__((used)) static int exec_get_raw_user_comm_updates (struct connection *c, const char *key, int key_len, int dog_len) {
  int user_id;
  int st_time = 0, end_time = 0, x = 0, raw = 0, mask = 0xffffffff;
  char *ptr;


  if (*key == '%') {
    raw = 1;
  }

  if ((sscanf (key+raw, "raw_user_comm_updates[%d,%d]:%n", &st_time, &end_time, &x) >= 2 ||
       sscanf (key+raw, "raw_user_comm_updates%n%d", &x, &user_id) >= 1) && x > 0) {
    x += raw;
    ptr = 0;
    user_id = strtol (key+x, &ptr, 10);
    if (ptr < key + key_len && *ptr == ',') {
      ptr ++;
      mask = strtol (ptr, &ptr, 10);
    }

    QL = get_bookmarks (user_id, mask, Q, MAX_QUERY / 3);
    if (verbosity >= 2) {
      fprintf (stderr, "QL = %d, bookmarks_size = %d\n", QL, bookmarks_size);
    }
    if (QL < 0) {
      return -2;
    }

    clear_result_buffer ();
    int i, best = 0;
    QL *= 3;
    assert (QL <= MAX_QUERY);
    for (i = 0; i < QL; i += 3) {
      int res = prepare_raw_comm_updates (Q[i], Q[i+1], Q[i+2], st_time, end_time);
      if (verbosity > 2) {
        fprintf (stderr, "prepare_raw_comm_updates(%d_%d_%d) = %d\n", Q[i], Q[i+1], Q[i+2], res);
      }
      if (res > best) {
        best = res;
      }
    }
    if (best >= 0) {
      return return_one_key_list (c, key - dog_len, key_len + dog_len, /*(R_end - R) / 9*/ 0x7fffffff, -raw, R, R_end - R);
    }
  }
  return 0;
}