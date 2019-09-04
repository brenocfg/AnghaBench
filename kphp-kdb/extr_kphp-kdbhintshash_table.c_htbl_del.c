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
typedef  int /*<<< orphan*/  hash_table ;

/* Variables and functions */
 int /*<<< orphan*/  chg_del (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htbl_find_or_create (int /*<<< orphan*/ *,long long) ; 

void htbl_del (hash_table *table, long long key, int val) {
  chg_del (htbl_find_or_create (table, key), val * 2 + 1);
}