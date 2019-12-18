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
 scalar_t__ INT_MIN ; 

__attribute__((used)) static inline unsigned long long make_value64 (int value, int x) {
  unsigned int a = value; a -= (unsigned int) INT_MIN;
  unsigned int b = x; b -= (unsigned int) INT_MIN;
  return (((unsigned long long) a) << 32) | b;
}