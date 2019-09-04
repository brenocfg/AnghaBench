#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int remaining; int* cur; unsigned long long value64; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 TYPE_1__** GH ; 
 TYPE_1__* GH_E ; 
 size_t GH_N ; 
 int GH_mode ; 
 int /*<<< orphan*/  GH_total ; 
 int TL_MAYBE_FALSE ; 
 int TL_MAYBE_TRUE ; 
 int /*<<< orphan*/  TL_VECTOR_TOTAL ; 
 int /*<<< orphan*/  load_heap_v (TYPE_1__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,...) ; 

__attribute__((used)) static int gather_heap_insert (int *data, int bytes) {
  if (bytes < 16) {
    vkprintf (2, "Bad result: bytes = %d\n", bytes);
    return -1;
  }
  if (*(data) == TL_MAYBE_FALSE) {
    return 0;
  }
  if (*(data) == TL_MAYBE_TRUE) {
    data ++;
    bytes -= 4;
  }
  if (*(data ++) != TL_VECTOR_TOTAL) {
    vkprintf (2, "Bad result: data = %d\n", *(data - 1));
    return -1;
  }
  gh_entry_t *H = &GH_E[GH_N];
  GH_total += *(data ++);
  H->remaining = *(data ++);
  int size = (GH_mode & 8) ? 1 : 2;
  if (H->remaining * size * 4 + 12 != bytes) {
    vkprintf (2, "Bad result: size = %d, H->remaining = %d, bytes = %d\n", size, H->remaining, bytes);
    return -1;
  }
  vkprintf (4, "gather_heap_insert: %d elements (size %d)\n", H->remaining, bytes - 12);
  if (!H->remaining) {
    return 0;
  }

  H->cur = data;
  load_heap_v (H);

  int i = ++GH_N, j;
  unsigned long long value64 = H->value64;
  while (i > 1) {
    j = (i >> 1);
    if (GH[j]->value64 <= value64) { break; }
    GH[i] = GH[j];
    i = j;
  }
  GH[i] = H;

  return 1;
}