#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int next; int y; long long value; } ;
struct TYPE_3__ {int user_id; int offset; } ;

/* Variables and functions */
 size_t MAX_NEW_BOOKMARK_USERS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* bookmarks ; 
 int bookmarks_ptr ; 
 TYPE_1__* new_users ; 
 size_t new_users_number ; 
 int next_bookmark_ptr () ; 

void build_bookmark_lists (void) {
  int i = bookmarks_ptr, user_id, q = 0, t;
  long long value;
  assert (!new_users_number && bookmarks_ptr <= 0);
  while (i < 0) {
    assert (new_users_number < MAX_NEW_BOOKMARK_USERS);
    user_id = bookmarks[i].next;
    if (!q) {
      t = next_bookmark_ptr ();
    } else {
      t = q;
      q = bookmarks[q].next;
    }
    new_users[new_users_number].user_id = user_id;
    new_users[new_users_number].offset = t;
    new_users_number++;
    do {
      bookmarks[t].next = i;
      bookmarks[i].y &= 1;
      t = i;
      value = bookmarks[i++].value;
      while (i < 0 && bookmarks[i].value == value && bookmarks[i].next == user_id) {
        bookmarks[i].next = q;
        q = i++;
      }
    } while (i < 0 && bookmarks[i].next == user_id);
    bookmarks[t].next = 0;
  }
}