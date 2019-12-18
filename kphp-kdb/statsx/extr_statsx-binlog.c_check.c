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
struct lev_generic {scalar_t__ a; } ;

/* Variables and functions */
 scalar_t__ ANY_COUNTER ; 
 scalar_t__ cnt_id ; 
 scalar_t__ now ; 
 scalar_t__ start_time ; 

inline int check (struct lev_generic *E) {
  return ((E->a == cnt_id || cnt_id == ANY_COUNTER) && now >= start_time);
}