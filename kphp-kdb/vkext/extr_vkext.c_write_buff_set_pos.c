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
 int buff ; 
 int cur_buff_len ; 
 int result_buff_pos ; 
 int wptr ; 

void write_buff_set_pos (int pos) {
  if (pos > cur_buff_len) {
    return;
  }
  if (pos >= result_buff_pos) {
    wptr = (pos - result_buff_pos) + buff;
    return;
  }
  //result_buff_pos -= (pos - (wptr - buff));
  result_buff_pos = pos;
  wptr = buff;
}