#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zn_zap; int /*<<< orphan*/  zn_hash; } ;
typedef  TYPE_1__ zap_name_t ;
typedef  int /*<<< orphan*/  zap_leaf_t ;
typedef  int /*<<< orphan*/  zap_entry_handle_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_WRITER ; 
 int zap_deref_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zap_entry_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_increment_num_entries (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int zap_leaf_lookup (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_put_leaf (int /*<<< orphan*/ *) ; 

int
fzap_remove(zap_name_t *zn, dmu_tx_t *tx)
{
	zap_leaf_t *l;
	int err;
	zap_entry_handle_t zeh;

	err = zap_deref_leaf(zn->zn_zap, zn->zn_hash, tx, RW_WRITER, &l);
	if (err != 0)
		return (err);
	err = zap_leaf_lookup(l, zn, &zeh);
	if (err == 0) {
		zap_entry_remove(&zeh);
		zap_increment_num_entries(zn->zn_zap, -1, tx);
	}
	zap_put_leaf(l);
	return (err);
}