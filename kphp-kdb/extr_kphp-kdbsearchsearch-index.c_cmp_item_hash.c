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
struct item {int dummy; } ;

/* Variables and functions */
 long long get_hash_item (struct item const*) ; 

int cmp_item_hash (const void *a, const void *b) {
  long long c = get_hash_item (* ((const struct item **) a));
  long long d = get_hash_item (* ((const struct item **) b));
  if (c < d) { return -1; }
  if (c > d) { return  1; }
  return 0;
}