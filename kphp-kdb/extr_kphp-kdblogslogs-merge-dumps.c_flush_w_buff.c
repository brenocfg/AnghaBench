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
 size_t ansI ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  w_buff ; 
 scalar_t__ w_buff_n ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void flush_w_buff() {
  write (fd[ansI], w_buff, w_buff_n);
  w_buff_n = 0;
}