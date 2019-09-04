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
 long dyn_cur ; 
 long dyn_first ; 
 int /*<<< orphan*/  dyn_update_stats () ; 
 long freed_bytes ; 

long dyn_used_memory (void) {
  dyn_update_stats();
  return (dyn_cur - dyn_first) - freed_bytes;
}