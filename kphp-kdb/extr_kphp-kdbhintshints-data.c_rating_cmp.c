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
typedef  scalar_t__ rating ;

/* Variables and functions */
 float fabsf (scalar_t__) ; 

inline int rating_cmp (rating a, rating b) {
  rating res = a - b;
  if (fabsf (res) < 1e-7f) {
    return 0;
  }
  if (res < 0) {
    return -1;
  }
  return 1;
}