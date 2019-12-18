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
 int split_mod ; 
 int split_rem ; 

int fits (int id) {
  if (!split_mod) {
    return 1;
  }
  if (id < 0) {
    id = -id;
  }
  return id % split_mod == split_rem;
}