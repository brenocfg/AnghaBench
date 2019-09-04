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
typedef  scalar_t__ hash_t ;
struct TYPE_2__ {scalar_t__ hash; int order; int message_id; } ;

/* Variables and functions */
 int* D ; 
 int Dc ; 
 TYPE_1__* P ; 
 int Pc ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int lookup_list (hash_t h, int **ptr) {
  int a = -1, b = Pc, c;
  while (b - a > 1) {
    c = (a + b) >> 1;
    if (P[c].hash <= h) a = c; else b = c;
  }

  if (a < 0 || P[a].hash != h) return 0;

  c = P[a].order;
  b = P[a].message_id;
  if (verbosity) {
    fprintf (stderr, "lookup_list: found hash=%llu, message/offset=%d, count=%d\n", h, b, c);
  }
  assert (c > 0 && (c <= Dc || c == 1));

  if (c == 1) {
    if (ptr) *ptr = &P[a].message_id;
    return c;
  }

  assert (b >= 0 && b + c <= Dc);
  if (ptr) *ptr = D + b;
  return c;
}