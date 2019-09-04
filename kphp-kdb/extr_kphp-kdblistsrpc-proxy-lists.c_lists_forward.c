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
 int TL_LISTS_DELETE_OBJECT ; 
 int default_query_diagonal_forward () ; 
 int default_tuple_forward_ext (int) ; 
 int tl_fetch_int () ; 
 int tl_fetch_lookup_int () ; 
 int /*<<< orphan*/  tl_fetch_mark () ; 

int lists_forward (void) {
  int op = tl_fetch_lookup_int ();
  if (op == TL_LISTS_DELETE_OBJECT) {
    return default_query_diagonal_forward ();
  } else {
    tl_fetch_mark ();
    tl_fetch_int ();
    int n = tl_fetch_int ();    
    return default_tuple_forward_ext (n);
  }
}