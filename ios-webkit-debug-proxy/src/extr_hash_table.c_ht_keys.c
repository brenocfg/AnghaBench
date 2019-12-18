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
typedef  int /*<<< orphan*/  ht_t ;

/* Variables and functions */
 void** ht_get_all (int /*<<< orphan*/ ,int) ; 

void **ht_keys(ht_t self) {
  return ht_get_all(self, 1);
}