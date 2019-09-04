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
struct bookmark_user {int user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int binary_search (int v, struct bookmark_user *users, int num) {
  int l = -1;
  int r = num;
  while (r - l > 1) {
    int x = (l + r) >> 1;
    assert (x >= 0);
    if (users[x].user_id <= v) {
      l = x;
    } else {
      r = x;
    }
  }
  if (l >= 0 && users[l].user_id == v) {
    return l;
  } else {
    return -1;
  }
}