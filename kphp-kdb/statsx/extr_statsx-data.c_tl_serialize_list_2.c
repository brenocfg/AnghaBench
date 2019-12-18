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
 int /*<<< orphan*/  tl_store_int (int) ; 
 int /*<<< orphan*/  tl_store_raw_data (int*,int) ; 

void tl_serialize_list_2 (int *ptr) {
  int e = ptr ? ptr[-1] : 0;
  tl_store_int (e);
  tl_store_raw_data (ptr, 8 * e);
}