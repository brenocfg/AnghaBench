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
struct index_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int index_entries ; 

struct index_entry *get_index_entry (int p) {
  assert (p >= 0 && p < index_entries);
  return 0;
}