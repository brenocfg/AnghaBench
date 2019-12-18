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
 int /*<<< orphan*/  Q ; 
 int QL ; 
 int /*<<< orphan*/  assert (int) ; 
 int bookmarks_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int get_bookmarks (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_one_key_list (struct connection*,char const*,int,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int strtol (char const*,char**,int) ; 
 int verbosity ; 

__attribute__((used)) static int exec_get_raw_user_comm_bookmarks (struct connection *c, const char *key, int key_len, int dog_len) {
  int user_id;
  int x = 0, raw = 0, mask = 0xffffffff;
  char *ptr;


  if (*key == '%') {
    raw = 1;
  }

  if ((sscanf (key+raw, "raw_user_comm_bookmarks%n", &x) >= 0) && x > 0) {
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
    assert (QL * 3 <= MAX_QUERY);
    return_one_key_list (c, key - dog_len, key_len + dog_len, 0x7fffffff, -raw, Q, QL * 3);
  }
  return 0;
}