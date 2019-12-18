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
 int tl_fetch_int_range (int,int) ; 

__attribute__((used)) static inline int tl_fetch_positive_int (void) {
  return tl_fetch_int_range (1, 0x7fffffff);
}