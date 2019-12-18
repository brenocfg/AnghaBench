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
 scalar_t__ dyn_cur ; 
 scalar_t__ dyn_first ; 
 scalar_t__ dyn_last ; 
 scalar_t__ dyn_top ; 

__attribute__((used)) static long heap_used (void) {
  return (long)(dyn_cur - dyn_first) + (long) (dyn_last - dyn_top);
}