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
 int MAX_ZMALLOC ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  zfree (void*,int) ; 

void tl_zzfree (void *src, int size) {
  if (!src) { return; }
  if (size <= MAX_ZMALLOC) {
    zfree (src, size);
  } else {
    free (src);
  }
}