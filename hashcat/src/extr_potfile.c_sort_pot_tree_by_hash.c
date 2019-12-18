#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * hashconfig; TYPE_1__* nodes; } ;
typedef  TYPE_2__ pot_tree_entry_t ;
typedef  int /*<<< orphan*/  hashconfig_t ;
typedef  int /*<<< orphan*/  hash_t ;
struct TYPE_3__ {scalar_t__ hash_buf; } ;

/* Variables and functions */
 int sort_by_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int sort_pot_tree_by_hash (const void *v1, const void *v2)
{
  const pot_tree_entry_t *t1 = (const pot_tree_entry_t *) v1;
  const pot_tree_entry_t *t2 = (const pot_tree_entry_t *) v2;

  const hash_t *h1 = (const hash_t *) t1->nodes->hash_buf;
  const hash_t *h2 = (const hash_t *) t2->nodes->hash_buf;

  hashconfig_t *hc = t1->hashconfig; // is same as t2->hashconfig

  return sort_by_hash (h1, h2, hc);
}