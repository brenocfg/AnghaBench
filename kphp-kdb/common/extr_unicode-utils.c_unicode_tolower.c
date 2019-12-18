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
 scalar_t__ TABLE_SIZE ; 
 int binary_search_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* to_lower_table ; 
 int /*<<< orphan*/  to_lower_table_ranges ; 
 int /*<<< orphan*/  to_lower_table_ranges_size ; 

int unicode_tolower (int code) {
  if ((unsigned int)code < (unsigned int)TABLE_SIZE) {
    return to_lower_table[code];
  } else {
    return binary_search_ranges (to_lower_table_ranges, to_lower_table_ranges_size, code);
  }
}