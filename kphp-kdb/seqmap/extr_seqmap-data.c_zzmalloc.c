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
 int MAX_ZMALLOC_MEM ; 
 int /*<<< orphan*/  PTRSIZE ; 
 int /*<<< orphan*/  assert (void*) ; 
 void* dyn_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_memory_used () ; 
 void* malloc (int) ; 
 int malloc_mem ; 
 scalar_t__ max_memory ; 
 int /*<<< orphan*/  stderr ; 
 int zalloc_mem ; 

void *zzmalloc (int size) {
  if (size < 0) { return 0; }
  void *res;

  if (get_memory_used () > max_memory) {
    fprintf (stderr, "too much memory used: %lld of %lld\n", (long long) get_memory_used (), (long long) max_memory);
//    fprintf (stderr, "memory distributes as follow: %lld to current, %lld to cache, %lld to metafiles, %lld to init data\n", entry_memory, cache_size, allocated_metafile_bytes, init_memory);
  }
  assert (get_memory_used () <= max_memory);

  if (size < MAX_ZMALLOC_MEM) {
    if (!(res = dyn_alloc (size, PTRSIZE))) {
      fprintf (stderr, "Out of memory\n");
    }
    assert (res);      
    zalloc_mem += size;
  } else {
    if (!(res = malloc (size))) {
      fprintf (stderr, "Out of memory\n");
    }
    assert (res);      
    malloc_mem += size;
  }

  assert(res);
  return res;
}