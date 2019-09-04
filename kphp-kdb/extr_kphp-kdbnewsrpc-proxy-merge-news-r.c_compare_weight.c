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
struct news_item {scalar_t__ weight; } ;

/* Variables and functions */

int compare_weight (const void *a, const void *b) {
  const struct news_item *A = a;
  const struct news_item *B = b;
  if (A->weight < B->weight) { return 1; }
  if (A->weight > B->weight) { return -1; }
  return 0;
}