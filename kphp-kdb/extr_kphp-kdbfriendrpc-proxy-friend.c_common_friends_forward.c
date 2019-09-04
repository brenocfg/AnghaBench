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
 int TL_FRIEND_COMMON_FRIENDS ; 
 int TL_FRIEND_COMMON_FRIENDS_NUM ; 
 int /*<<< orphan*/  common_friends_gather_methods ; 
 int /*<<< orphan*/  common_friends_num_gather_methods ; 
 int default_firstint_forward () ; 
 int /*<<< orphan*/  merge_forward (int /*<<< orphan*/ *) ; 
 int tl_fetch_lookup_int () ; 

int common_friends_forward (void) {
  int op = tl_fetch_lookup_int (); // op
  if (op == TL_FRIEND_COMMON_FRIENDS) {
    merge_forward (&common_friends_gather_methods);
    return 0;
  } else if (op == TL_FRIEND_COMMON_FRIENDS_NUM) {
    merge_forward (&common_friends_num_gather_methods);
    return 0;
  } else {
    return default_firstint_forward ();
  }
}