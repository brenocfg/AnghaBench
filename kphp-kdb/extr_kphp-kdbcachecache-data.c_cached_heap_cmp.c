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
 int uncached_heap_cmp (void const*,void const*) ; 

__attribute__((used)) static int cached_heap_cmp (const void *a, const void *b) {
  return uncached_heap_cmp (b, a);
}