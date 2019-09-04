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
 int /*<<< orphan*/  out_buf_init ; 
 int /*<<< orphan*/  out_buf_next ; 
 int /*<<< orphan*/  out_buf_prev ; 

int out_buf_clean (void) {
  return !out_buf_init && !out_buf_prev && !out_buf_next;
}