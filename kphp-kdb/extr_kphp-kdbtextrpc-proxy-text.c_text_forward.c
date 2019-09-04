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
 int TL_TEXT_GET_EXTRA_MASK ; 
 int TL_TEXT_OFFLINE ; 
 int TL_TEXT_ONLINE ; 
 int TL_TEXT_PEERMSG_TYPE ; 
 int TL_TEXT_SET_EXTRA_MASK ; 
 int TL_TEXT_SUBLIST_TYPES ; 
 int default_firstint_forward () ; 
 int default_query_diagonal_forward () ; 
 int default_random_forward () ; 
 int /*<<< orphan*/  merge_forward (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_online_gather_methods ; 
 int tl_fetch_lookup_int () ; 

int text_forward (void) {
  int op = tl_fetch_lookup_int ();
  if (op == TL_TEXT_SET_EXTRA_MASK) {
    return default_query_diagonal_forward ();
  } else if (op == TL_TEXT_ONLINE || op == TL_TEXT_OFFLINE) {
    merge_forward (&text_online_gather_methods);
    return 0;
  } else if (op == TL_TEXT_SUBLIST_TYPES || op == TL_TEXT_PEERMSG_TYPE || op == TL_TEXT_GET_EXTRA_MASK) {
    return default_random_forward ();
  } else {
    return default_firstint_forward ();
  }
}