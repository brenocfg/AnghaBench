#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * e; scalar_t__ size; scalar_t__ n; } ;
typedef  TYPE_1__ qhash_table ;

/* Variables and functions */

void qhtbl_init (qhash_table *ht) {
  ht->n = 0;
  ht->size = 0;
  ht->e = NULL;
}