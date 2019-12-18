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
 int /*<<< orphan*/  assert (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int tot_memory_allocated ; 
 void* zmalloc0 (int) ; 

void *zzmalloc0 (int l) {
  void *t;
  if (l < MAX_ZALLOC) {
    t = zmalloc0 (l);
  } else {
    t = malloc (l);
    assert (t);
    memset (t, 0, l);
  }
  if (t) {
    tot_memory_allocated += l;
  }
  return t;
}