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
typedef  int /*<<< orphan*/  hash_entry ;

/* Variables and functions */
 int htbl_allocated_cnt ; 

size_t htbl_get_memory (void) {
  return htbl_allocated_cnt * sizeof (hash_entry);
}