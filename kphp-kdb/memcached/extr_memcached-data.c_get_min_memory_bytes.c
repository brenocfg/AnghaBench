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
typedef  int /*<<< orphan*/  time_st ;
typedef  int /*<<< orphan*/  hash_st ;
typedef  int /*<<< orphan*/  entry_buffer ;
typedef  int /*<<< orphan*/  buffer_stack ;

/* Variables and functions */

long get_min_memory_bytes (void) {
  return (sizeof (entry_buffer) + sizeof (buffer_stack) + sizeof (hash_st) + sizeof (time_st)) ;
}