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
typedef  int /*<<< orphan*/  value_t ;
typedef  int /*<<< orphan*/  global_id_t ;

/* Variables and functions */
 int /*<<< orphan*/ * H ; 
 int HN ; 
 scalar_t__ heap_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int heap_sift_up (value_t value, global_id_t global_id) {
  int i = ++HN, j;
  while (i > 1) {
    j = (i >> 1);
    if (heap_cmp (&H[j], value, global_id) <= 0) {
      break;
    }
    H[i] = H[j];
    i = j;
  }
  return i;
}