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
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  zfree (void*,long) ; 

__attribute__((used)) static inline void metafile_free (void *ptr, long size) {
  allocated_metafiles_size -= size;
  if (size >= METAFILE_MALLOC_THRESHOLD) {
    free (ptr);
  } else {
    zfree (ptr, size);
  }
}