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
 char* buff ; 
 int cur_buff_len ; 
 char* result_buff ; 
 int result_buff_pos ; 

void write_buff_char_pos (char c, int pos) {
  if (pos > cur_buff_len) {
    return;
  }
  if (pos >= result_buff_pos) {
    *((pos - result_buff_pos) + buff) = c;
    return;
  }
  //*(result_buff + result_buff_pos - (pos - (wptr - buff))) = c;
  *(result_buff + pos) = c;
}