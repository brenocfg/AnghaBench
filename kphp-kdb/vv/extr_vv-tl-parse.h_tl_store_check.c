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
 int TL_OUT_REMAINING ; 
 scalar_t__ TL_OUT_TYPE ; 
 scalar_t__ tl_type_none ; 

__attribute__((used)) static inline int tl_store_check (int size) {
  if (TL_OUT_TYPE == tl_type_none) { return -1; }
  if (TL_OUT_REMAINING < size) { return -1; }
  return 0;
}