#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* cur; int x; int value; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 int GH_mode ; 
 int g_desc ; 
 int g_double ; 

__attribute__((used)) static inline void load_heap_v (gh_entry_t *H) {
  int *data = H->cur;
  int x = (data[1] ? data[1] : data[0]);
  int value = (GH_mode & g_double ? data[2] : x);
  if (GH_mode & g_desc) {
    H->x = -x;
    H->value = -value;
  } else {
    H->x = x;
    H->value = value;
  }
}