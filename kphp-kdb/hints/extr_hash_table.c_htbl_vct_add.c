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
typedef  int /*<<< orphan*/  hash_table_vct ;

/* Variables and functions */
 int /*<<< orphan*/  htbl_vct_find_or_create (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  vct_set_add (int /*<<< orphan*/ ,int) ; 

void htbl_vct_add (hash_table_vct *table, long long key, int val) {
  vct_set_add (htbl_vct_find_or_create (table, key), val);
}