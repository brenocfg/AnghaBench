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
 int __builtin_ctz (unsigned int) ; 

__attribute__((used)) static int b_log2 (unsigned x) {
  x &= -x;
  return x ? __builtin_ctz (x) : -1;
}