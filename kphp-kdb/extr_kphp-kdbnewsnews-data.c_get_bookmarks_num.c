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
 scalar_t__ advance_iterator () ; 
 int init_iterator (int,int) ; 

int get_bookmarks_num (int user_id, int use_aio) {
  int res = init_iterator (user_id, use_aio);
  if (res < 0) {
    return res;
  }
  res = 0;
  while (advance_iterator () >= 0) {
    res ++;
  }
  return res;
}