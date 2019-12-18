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
 int GA ; 
 int GB ; 

int is_friend (int x, int y) {
  int a = -1, b = ((GB - GA) >> 3), c;
  int *Q = (int *) GA;
  while (b - a > 1) {
    c = ((a + b) >> 1);
    if (Q[2*c] < x || (Q[2*c] == x && Q[2*c+1] <= y)) {
      a = c;
    } else {
      b = c;
    }
  }
  return (a >= 0 && Q[2*a] == x && Q[2*a+1] == y);
}