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
 int key_cmp2 (int,int const*,int,int const*,int /*<<< orphan*/ ) ; 

int key_cmp (int l1, const int *k1, int l2, const int *k2) {
  return key_cmp2 (l1, k1, l2, k2, 0);
}