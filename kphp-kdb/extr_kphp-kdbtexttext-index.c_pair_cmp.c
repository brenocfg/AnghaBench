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
struct pair {scalar_t__ key; int local_id; } ;

/* Variables and functions */

__attribute__((used)) static inline int pair_cmp (struct pair *a, struct pair *b) {
  if (a->key < b->key) {
    return -1;
  } else if (a->key > b->key) {
    return 1;
  }
  return a->local_id - b->local_id;
}