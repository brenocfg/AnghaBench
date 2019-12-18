#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int remaining; int* cur; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 TYPE_1__** GH ; 
 TYPE_1__* GH_E ; 
 size_t GH_N ; 
 int /*<<< orphan*/  GH_total ; 
 int /*<<< orphan*/  TL_VECTOR_TOTAL ; 
 scalar_t__ gh_entry_less (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  load_heap_v (TYPE_1__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,...) ; 

__attribute__((used)) static int gather_heap_insert (int *data, int bytes) {
  if (bytes < 12) {
    vkprintf (2, "Bad result: bytes = %d\n", bytes);
    return -1;
  }
  if (*data++ != TL_VECTOR_TOTAL) {
    vkprintf (2, "Bad result: data = %08x\n", data[-1]);
    return -1;
  }
  gh_entry_t *H = &GH_E[GH_N];
  GH_total += *data++;
  H->remaining = *data++;
  if (H->remaining * 4 * 4 + 12 != bytes) {
    vkprintf (2, "Bad result: H->remaining = %d, bytes = %d\n", H->remaining, bytes);
    return -1;
  }
  vkprintf (4, "gather_heap_insert: %d elements (size %d)\n", H->remaining, bytes - 12);
  if (!H->remaining) {
    return 0;
  }

  H->cur = data;
  load_heap_v (H);

  int i = ++GH_N, j;
  while (i > 1) {
    j = (i >> 1);
    if (gh_entry_less (GH[j], H)) {
      break;
    }
    GH[i] = GH[j];
    i = j;
  }
  GH[i] = H;

  return 1;
}