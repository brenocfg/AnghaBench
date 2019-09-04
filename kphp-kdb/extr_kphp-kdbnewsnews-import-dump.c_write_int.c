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
 scalar_t__ WRITE_BUFF_SIZE ; 
 int /*<<< orphan*/  flush_write (int) ; 
 scalar_t__* wptr ; 
 scalar_t__* write_buff ; 

void write_int (int x, int d) {
  if (wptr[x] + 4 > write_buff[x] + WRITE_BUFF_SIZE)  {
    flush_write (x);
  }
  //fprintf (stderr, ".");
  //assert (*(int *)(wptr[x]) == 0);
  *(int *)(wptr[x]) = d;
  wptr[x] += 4;
}