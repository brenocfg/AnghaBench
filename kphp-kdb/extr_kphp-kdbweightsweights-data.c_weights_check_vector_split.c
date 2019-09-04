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
 int igcd (int /*<<< orphan*/ ,int) ; 
 int log_split_min ; 
 int /*<<< orphan*/  log_split_mod ; 

int weights_check_vector_split (int vector_rem, int vector_mod) {
  // x * split_mod + split_min = y * vector_mod + vector_rem
  // x * split_mod - y * vector_mod = vector_rem - split_min
  int g = igcd (log_split_mod, vector_mod);
  if ((vector_rem - log_split_min) % g) {
    return -1;
  }
  return 0;
}