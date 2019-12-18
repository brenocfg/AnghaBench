#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int next_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_by_LRU ; 
 int /*<<< orphan*/  del_entry (int) ; 
 TYPE_1__* entry_buffer ; 

int free_LRU (void) {
  int used_st = entry_buffer[0].next_used;
  if (used_st == 0) {
    return -1;
  }

  del_by_LRU++;
  del_entry (used_st);

  return 0;
}