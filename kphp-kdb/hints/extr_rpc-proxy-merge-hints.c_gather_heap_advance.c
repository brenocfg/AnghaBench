#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  remaining; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 TYPE_1__** GH ; 
 int GH_N ; 
 scalar_t__ gh_entry_less (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  load_heap_v (TYPE_1__*) ; 

__attribute__((used)) static void gather_heap_advance (void) {
  if (!GH_N) {
    return;
  }

  gh_entry_t *H = GH[1];
  if (!H->remaining) {
    H = GH[GH_N--];
    if (!GH_N) {
      return;
    }
  } else {
    load_heap_v (H);
  }

  int i = 1;
  while (1) {
    int j = i * 2;
    if (j > GH_N) {
      break;
    }
    if (j < GH_N && gh_entry_less (GH[j + 1], GH[j])) {
      j++;
    }
    if (!gh_entry_less (GH[j], H)) {
      break;
    }
    GH[i] = GH[j];
    i = j;
  }
  GH[i] = H;
}