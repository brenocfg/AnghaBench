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
typedef  int /*<<< orphan*/  mchunkptr ;

/* Variables and functions */
 size_t chunksize (int /*<<< orphan*/ ) ; 
 scalar_t__ cinuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem2chunk (void*) ; 
 size_t overhead_for (int /*<<< orphan*/ ) ; 

size_t dlmalloc_usable_size(void* mem) {
  if (mem != 0) {
    mchunkptr p = mem2chunk(mem);
    if (cinuse(p))
      return chunksize(p) - overhead_for(p);
  }
  return 0;
}