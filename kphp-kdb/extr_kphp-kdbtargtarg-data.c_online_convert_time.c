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
 int OLIST_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_valid_online_stamp (int) ; 
 int ocur_now ; 
 int ocur_ptr ; 

__attribute__((used)) static inline int online_convert_time (int ts) {
  assert (ocur_now && is_valid_online_stamp (ts));
  if (ts > ocur_now) {
    return ocur_ptr;
  }
  int res = ts - ocur_now + ocur_ptr;
  if (res < 0) {
    res += OLIST_COUNT;
  }
  assert (res >= 0 && res < OLIST_COUNT);
  return res;
}