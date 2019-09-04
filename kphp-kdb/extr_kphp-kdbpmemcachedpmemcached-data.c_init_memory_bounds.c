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
 int MEMORY_FOR_CACHE ; 
 int MEMORY_FOR_METAFILES ; 
 int MEMORY_FOR_WILDCARD_CACHE ; 
 int MEMORY_RESERVED ; 
 long long MIN_MEMORY_FOR_CACHE ; 
 long long MIN_MEMORY_FOR_METAFILES ; 
 long long MIN_MEMORY_FOR_WILDCARD_CACHE ; 
 long long init_memory ; 
 int max_memory ; 
 long long memory_for_cache ; 
 long long memory_for_entries ; 
 long long memory_for_metafiles ; 
 long long memory_for_wildcard_cache ; 

void init_memory_bounds (void) {
  memory_for_metafiles = (long long) (MEMORY_FOR_METAFILES * max_memory);
  if (memory_for_metafiles < MIN_MEMORY_FOR_METAFILES) {
    memory_for_metafiles = MIN_MEMORY_FOR_METAFILES;
  }
  memory_for_cache = (long long) (MEMORY_FOR_CACHE * max_memory);
  if (memory_for_cache < MIN_MEMORY_FOR_CACHE) {
    memory_for_cache = MIN_MEMORY_FOR_CACHE;
  }
  memory_for_wildcard_cache = (long long) (MEMORY_FOR_WILDCARD_CACHE * max_memory);
  if (memory_for_wildcard_cache < MIN_MEMORY_FOR_WILDCARD_CACHE) {
    memory_for_wildcard_cache = MIN_MEMORY_FOR_WILDCARD_CACHE;
  }
  memory_for_entries = (long long) ((1 - MEMORY_RESERVED) * max_memory) - memory_for_cache - memory_for_metafiles - init_memory;
}