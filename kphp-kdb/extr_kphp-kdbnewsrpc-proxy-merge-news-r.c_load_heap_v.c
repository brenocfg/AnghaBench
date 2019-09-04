#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int owner; int place; } ;
struct TYPE_5__ {int* cur; TYPE_1__ id; } ;
typedef  TYPE_2__ gh_entry_t ;

/* Variables and functions */

__attribute__((used)) static inline void load_heap_v (gh_entry_t *H) {
  int *data = H->cur;
  H->id.type = data[0];
  H->id.owner = data[1];
  H->id.place = data[2];
}