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
 int BUFF_SIZE ; 
 int /*<<< orphan*/  flush_w_buff () ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 
 int w_buff ; 
 int w_buff_n ; 

void my_write (char *s, int n) {
  int i = 0;
  while (i < n) {
    int x = n - i;
    if (x > BUFF_SIZE - w_buff_n) {
      x = BUFF_SIZE - w_buff_n;
    }
    memcpy (w_buff + w_buff_n, s + i, x);
    i += x;
    w_buff_n += x;
    if (w_buff_n == BUFF_SIZE) {
      flush_w_buff();
    }
  }
}