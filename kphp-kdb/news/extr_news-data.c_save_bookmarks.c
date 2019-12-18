#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bookmark_user {int dummy; } ;
struct TYPE_4__ {int small_data_offset; int large_data_offset; int small_users; int large_users; } ;
typedef  TYPE_1__ index_header ;
struct TYPE_5__ {int value; } ;

/* Variables and functions */
 scalar_t__ ALLOW_OLD_INDEX_MODE ; 
 int ANS_BUFF_SIZE ; 
 int ANS_BUFF_SIZE_SMALLER ; 
 int MAX_SMALL_BOOKMARK ; 
 scalar_t__ advance_user_iterator () ; 
 int /*<<< orphan*/  ans_buff ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bookmarks ; 
 int bookmarks_ptr ; 
 int /*<<< orphan*/  build_bookmark_lists () ; 
 int /*<<< orphan*/  clearin () ; 
 int /*<<< orphan*/  flushout () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_bookmarks_num (int,int) ; 
 int get_bookmarks_packed (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  init_user_iterator () ; 
 int /*<<< orphan*/  sort_bookmarks (scalar_t__,int) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__ user_iterator ; 
 int verbosity ; 
 int /*<<< orphan*/  writeint (int) ; 
 int /*<<< orphan*/  writeout (int /*<<< orphan*/ ,int) ; 

void save_bookmarks (index_header *header) {
  clearin ();
  int small_offset = 0;
  int large_offset = 0;
  int small_users_n = 0;
  int large_users_n = 0;
  if (index_mode > ALLOW_OLD_INDEX_MODE && bookmarks_ptr) {
    assert (bookmarks_ptr < 0 && bookmarks);
    if (verbosity > 0) {
      fprintf (stderr, "sorting %d bookmarks...\n", -bookmarks_ptr);
    }
    sort_bookmarks (bookmarks + bookmarks_ptr, - bookmarks_ptr - 1);
    if (verbosity > 0) {
      fprintf (stderr, "building bookmark lists...\n");
    }
    build_bookmark_lists ();
  }
  if (verbosity > 0) {
    fprintf (stderr, "writing bookmark lists...\n");
  }
  init_user_iterator ();
  int total_users = 0;
  while (advance_user_iterator () >= 0) {
    int user_id = user_iterator.value;
    int n = get_bookmarks_num (user_id, -1);
    assert (n >= 0);
    total_users++;
    if (verbosity >= 4) {
      fprintf (stderr, "user #%d: %d, n = %d, max_small = %d, small_cnt = %d\n", total_users, user_id, n, MAX_SMALL_BOOKMARK, small_users_n);
    }
    if (n == 0) {
      continue;
    }
    assert (n > 0);
    if (n <= MAX_SMALL_BOOKMARK) {
      writeint (user_id);
      writeint (small_offset);
      small_offset += n;
      assert (small_offset >= 0);
      small_users_n ++;
    }
  }
  writeint (0);
  writeint (small_offset);
  init_user_iterator ();
  while (advance_user_iterator () >= 0) {
    int user_id = user_iterator.value;
    int n = get_bookmarks_num (user_id, -1);
    assert (n >= 0);
    if (n == 0) {
      continue;
    }
    assert (n > 0);
    if (n > MAX_SMALL_BOOKMARK) {
      if (n > ANS_BUFF_SIZE) {
        n = ANS_BUFF_SIZE_SMALLER;
      }
      writeint (user_id);
      writeint (large_offset);
      large_offset += n;
      assert (large_offset >= 0);
      large_users_n ++;
    }
  }
  writeint (0);
  writeint (large_offset);
  small_offset = 0;
  init_user_iterator ();
  while (advance_user_iterator () >= 0) {
    int user_id = user_iterator.value;
    int n = get_bookmarks_num (user_id, -1);
    assert (n >= 0);
    if (n == 0) {
      continue;
    }
    assert (n > 0);
    if (n <= MAX_SMALL_BOOKMARK) {
      assert (n == get_bookmarks_packed (user_id, ans_buff, ANS_BUFF_SIZE));
      assert (n <= ANS_BUFF_SIZE);
      small_offset += n;
      writeout (ans_buff, n * sizeof (long long));
    }
  }
  large_offset = 0;
  init_user_iterator ();
  while (advance_user_iterator () >= 0) {
    int user_id = user_iterator.value;
    int n = get_bookmarks_num (user_id, -1);
    assert (n >= 0);
    if (n == 0) {
      continue;
    }
    assert (n > 0);
    if (n > MAX_SMALL_BOOKMARK) {
      if (n > ANS_BUFF_SIZE) {
        fprintf (stderr, "user %d: has %d bookmarks, leaving only %d in index\n", user_id, n, ANS_BUFF_SIZE_SMALLER);
        n = ANS_BUFF_SIZE_SMALLER;
      }
      assert (n == get_bookmarks_packed (user_id, ans_buff, n));
      assert (n <= ANS_BUFF_SIZE);
      large_offset += n;
      writeout (ans_buff, n * sizeof (long long));
    }
  }
  flushout ();

  header->small_data_offset = (small_users_n + 1) * sizeof (struct bookmark_user) + (large_users_n + 1) * sizeof (struct bookmark_user);
  header->large_data_offset = header->small_data_offset + sizeof (long long) * small_offset;
  header->small_users = small_users_n;
  header->large_users = large_users_n;

  if (verbosity) {
    fprintf (stderr, "small_users = %d, large_users = %d\n", small_users_n, large_users_n);
  }
}