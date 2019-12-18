#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bookmark_user {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  next; } ;
struct TYPE_5__ {int user_id; size_t offset; } ;

/* Variables and functions */
 int MAX_NEW_BOOKMARK_USERS ; 
 int /*<<< orphan*/  NIL_BOOKMARK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* bookmarks ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* new_users ; 
 int new_users_number ; 
 size_t next_bookmark_ptr () ; 

int insert_new_users (int user_id) {
  int l = -1;
  int r = new_users_number;
  while (r - l > 1) {
    int x = (r + l) >> 1;
    if (new_users[x].user_id <= user_id) {
      l = x;
    } else {
      r = x;
    }
  }
  if (l >= 0 && new_users[l].user_id == user_id) {
    return l;
  }
  l++;
  assert (new_users_number < MAX_NEW_BOOKMARK_USERS);
  memmove (new_users + l + 1, new_users + l, sizeof (struct bookmark_user) * (new_users_number - l));
  new_users[l].user_id = user_id;
  new_users[l].offset = next_bookmark_ptr ();
  bookmarks[new_users[l].offset].next = NIL_BOOKMARK;
  new_users_number ++;
  return l;
}