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
 long METAFILE_MALLOC_THRESHOLD ; 
 long allocated_metafiles_size ; 
 void* malloc (long) ; 
 void* zmalloc (long) ; 

__attribute__((used)) static inline void *metafile_alloc (long size) {
  void *ptr = (size >= METAFILE_MALLOC_THRESHOLD ? malloc (size) : zmalloc (size));
  if (ptr) {
    allocated_metafiles_size += size;
  }
  return ptr;
}