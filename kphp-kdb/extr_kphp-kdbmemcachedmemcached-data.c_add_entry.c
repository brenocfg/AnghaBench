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
struct TYPE_2__ {int next_entry; int /*<<< orphan*/  key_hash; } ;

/* Variables and functions */
 int GET_ENTRY_ID (int /*<<< orphan*/ ) ; 
 TYPE_1__* entry_buffer ; 
 int* hash_st ; 

void add_entry (int x) {
  int i = GET_ENTRY_ID (entry_buffer[x].key_hash);

  entry_buffer[x].next_entry = hash_st[i];
  hash_st[i] = x;
}