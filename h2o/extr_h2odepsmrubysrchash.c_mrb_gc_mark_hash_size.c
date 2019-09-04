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
struct RHash {TYPE_1__* ht; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */

size_t
mrb_gc_mark_hash_size(mrb_state *mrb, struct RHash *hash)
{
  if (!hash->ht) return 0;
  return hash->ht->size*2;
}