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
 int log_cur_pos () ; 
 int split_par ; 
 int split_quotient ; 
 int split_shift ; 

void adjust_split_params (void) {
  split_par = (split_shift + (log_cur_pos() >> 2)) % split_quotient;
  if (split_par < 0) {
    split_par = -split_par;
  }
}