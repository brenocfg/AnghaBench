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
typedef  int /*<<< orphan*/  uint16_t ;
struct ck_ht_hash {int dummy; } ;
struct ck_ht {int /*<<< orphan*/  seed; int /*<<< orphan*/  (* h ) (struct ck_ht_hash*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ck_ht_hash*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ck_ht_hash(struct ck_ht_hash *h,
    struct ck_ht *table,
    const void *key,
    uint16_t key_length)
{

	table->h(h, key, key_length, table->seed);
	return;
}