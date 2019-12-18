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
 scalar_t__ buffer_meta_number ; 
 scalar_t__ buffer_meta_pos ; 
 scalar_t__* buffer_shifts ; 
 int /*<<< orphan*/  write_buffer_number ; 

void buffer_meta_init () {
  buffer_meta_pos = 0;
  buffer_meta_number = 0;
  buffer_shifts[0] = 0;
  write_buffer_number++;
}