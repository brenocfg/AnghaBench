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
struct TYPE_3__ {int /*<<< orphan*/  hash; int /*<<< orphan*/ * h; scalar_t__ size; } ;
typedef  TYPE_1__ hash_table ;

/* Variables and functions */
 int /*<<< orphan*/  poly_h (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void htbl_init (hash_table *table) {
  table->size = 0;
  table->h = NULL;
  table->hash = poly_h (NULL, 0);
}