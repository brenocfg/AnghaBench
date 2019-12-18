#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct news_item {scalar_t__ weight; } ;
struct TYPE_2__ {struct news_item entry; } ;

/* Variables and functions */
 TYPE_1__* UH ; 
 void* UH_limit ; 
 void* UH_size ; 
 void* UH_total ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  union_heap_insert (struct news_item) ; 

__attribute__((used)) static void union_heap_to_array (void) {  
  int p;
  UH_total = UH_size;
  for (p = UH_size; p >= 2; p--) {
    struct news_item x = UH[p].entry;
    assert (UH[1].entry.weight <= x.weight);
    UH[p].entry = UH[1].entry;
    UH_size --;
    UH_limit = UH_size;
    union_heap_insert (x);
  }
}