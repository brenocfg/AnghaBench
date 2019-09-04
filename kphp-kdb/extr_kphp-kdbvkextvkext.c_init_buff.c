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
 int /*<<< orphan*/  buff ; 
 scalar_t__ result_buff_len ; 
 scalar_t__ result_buff_pos ; 
 int /*<<< orphan*/  wptr ; 

void init_buff () {
  //buff_pos = 0;
  wptr = buff;
  result_buff_len = 0;
  result_buff_pos = 0;
}