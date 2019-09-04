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
 int MAX_EXTRA_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int read_extra_mask ; 
 int write_extra_mask ; 

__attribute__((used)) static void change_extra_mask (int value) {
  assert (!(value & ~MAX_EXTRA_MASK));
  read_extra_mask &= write_extra_mask = value;
}