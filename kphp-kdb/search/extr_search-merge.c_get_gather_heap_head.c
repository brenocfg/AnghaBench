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
struct TYPE_2__ {int* cur; } ;

/* Variables and functions */
 TYPE_1__** GH ; 
 scalar_t__ GH_N ; 

__attribute__((used)) static int *get_gather_heap_head (void) {
  return GH_N ? GH[1]->cur : 0;
}