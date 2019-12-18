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
struct TYPE_5__ {scalar_t__ size; unsigned int n; TYPE_1__* e; } ;
typedef  TYPE_2__ qhash_table ;
typedef  int /*<<< orphan*/  pair ;
typedef  scalar_t__ ll ;
struct TYPE_4__ {scalar_t__ h; int /*<<< orphan*/  val; } ;

/* Variables and functions */

inline pair *qhtbl_get (qhash_table *ht, ll h) {
  if (ht->size == 0) {
    return NULL;
  }
  int i = (unsigned int)h % ht->n;

  while (ht->e[i].h != h && ht->e[i].h) {
    if (++i == ht->n) {
      i = 0;
    }
  }

  return ht->e[i].h ? &ht->e[i].val : NULL;
}