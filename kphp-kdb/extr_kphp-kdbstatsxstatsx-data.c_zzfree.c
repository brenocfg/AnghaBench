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
 int MAX_ZALLOC ; 
 int /*<<< orphan*/  free (void*) ; 
 int tot_memory_allocated ; 
 int /*<<< orphan*/  zfree (void*,int) ; 

void zzfree (void *p, int l) {
  if (l < MAX_ZALLOC) {
    zfree (p, l);
  } else {
    free (p);
  }
  tot_memory_allocated -= l;
}