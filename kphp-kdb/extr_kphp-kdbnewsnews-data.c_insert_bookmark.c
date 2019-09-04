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
struct TYPE_5__ {int next; int y; long long value; } ;
struct TYPE_4__ {int offset; } ;

/* Variables and functions */
 scalar_t__ ALLOW_OLD_INDEX_MODE ; 
 int NIL_BOOKMARK ; 
 int /*<<< orphan*/  assert (int) ; 
 int binary_search (int,TYPE_1__*,int) ; 
 TYPE_2__* bookmarks ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ index_mode ; 
 int insert_new_users (int) ; 
 TYPE_1__* new_users ; 
 int new_users_number ; 
 int next_bookmark_ptr () ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int insert_bookmark (int user_id, long long value, int y, int write) {
  if (index_mode > ALLOW_OLD_INDEX_MODE) {
    int t = next_bookmark_ptr ();
    assert (write && (t & 0xc0000000) == 0xc0000000);	// won't work in BOOKMARK_MALLOC mode
    bookmarks[t].next = user_id;
    bookmarks[t].y = (t << 1) + (y & 1);
    bookmarks[t].value = value;
    return 1;
  }
  int t = binary_search (user_id, new_users, new_users_number);
  if (t < 0) {
    if (!write) {
      return 0;
    }
    t = insert_new_users (user_id);
    assert (t == binary_search (user_id, new_users, new_users_number));
    if (verbosity >= 4) {
      fprintf (stderr, "Inserted user %d (total %d new users)\n", user_id, new_users_number);
    }
  }
  int x = new_users[t].offset;
  while (1) {
    int x1 = bookmarks[x].next;
    if (x1 == NIL_BOOKMARK || bookmarks[x1].value > value) {
      if (!write) {
        return 0;
      }
      int t = next_bookmark_ptr ();
      bookmarks[t].next = x1;
      bookmarks[t].value = value;
      bookmarks[t].y = y;
      bookmarks[x].next = t;
      break;
    }
    if (bookmarks[x1].value == value) {
      if (!write) {
        return bookmarks[x1].y == y;
      }
      if (y != bookmarks[x1].y) {
        bookmarks[x1].y = y;
      }
      break;
    }
    x = x1;
  }
  return 1;
}