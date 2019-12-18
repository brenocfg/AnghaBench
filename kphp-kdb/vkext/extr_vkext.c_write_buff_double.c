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
 scalar_t__ BUFF_LEN ; 
 scalar_t__ buff ; 
 int /*<<< orphan*/  flush_buff () ; 
 scalar_t__ sprintf (scalar_t__,char*,double) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wptr ; 

void write_buff_double (double x) {
  if (unlikely (wptr + 100 > buff + BUFF_LEN)) {
    flush_buff ();
  }
  wptr += sprintf (wptr, "%lf", x);
}