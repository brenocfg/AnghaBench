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
struct ck_ht_hash {int dummy; } ;
struct ck_ht {int dummy; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  ck_ht_hash (struct ck_ht_hash*,struct ck_ht*,uintptr_t*,int) ; 

void
ck_ht_hash_direct(struct ck_ht_hash *h,
    struct ck_ht *table,
    uintptr_t key)
{

	ck_ht_hash(h, table, &key, sizeof(key));
	return;
}