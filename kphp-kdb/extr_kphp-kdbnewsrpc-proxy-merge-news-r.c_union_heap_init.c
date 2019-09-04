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
struct union_heap_entry {int dummy; } ;

/* Variables and functions */
 int UH ; 
 int UH_allocated ; 
 int UH_limit ; 
 scalar_t__ UH_size ; 
 scalar_t__ UH_total ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int) ; 
 int malloc (int) ; 

__attribute__((used)) static void union_heap_init (int size) {
  if (UH_allocated < size) {
    if (UH_allocated) {
      free (UH);
    }
    UH = malloc (sizeof (struct union_heap_entry) * (size + 1));
    assert (UH);
    UH_allocated = size;
  }
  assert (size <= UH_allocated);
  UH_limit = size;
  UH_size = 0;
  UH_total = 0;
}