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
 int* __a ; 
 int __c ; 
 int __f ; 

void __rx_do (int t) {
  if (__f < t && __c < 50) {
    __a[2 * __c + 0] = __f;
    __a[2 * __c + 1] = t - 1;
    __c ++;
  }
  __f = t + 1;
}