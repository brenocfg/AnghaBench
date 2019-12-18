#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int zn_key_orig_numints; int zn_key_intlen; int /*<<< orphan*/  zn_hash; } ;
typedef  TYPE_1__ zap_name_t ;
typedef  int /*<<< orphan*/  zap_leaf_t ;
struct TYPE_9__ {int /*<<< orphan*/  zeh_cd; int /*<<< orphan*/  zeh_hash; } ;
typedef  TYPE_2__ zap_entry_handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  zc_cd; int /*<<< orphan*/  zc_hash; int /*<<< orphan*/ * zc_leaf; int /*<<< orphan*/  zc_zap; } ;
typedef  TYPE_3__ zap_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZAP_MAXNAMELEN ; 
 int zap_deref_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int zap_leaf_lookup (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 

int
fzap_cursor_move_to_key(zap_cursor_t *zc, zap_name_t *zn)
{
	int err;
	zap_leaf_t *l;
	zap_entry_handle_t zeh;

	if (zn->zn_key_orig_numints * zn->zn_key_intlen > ZAP_MAXNAMELEN)
		return (SET_ERROR(ENAMETOOLONG));

	err = zap_deref_leaf(zc->zc_zap, zn->zn_hash, NULL, RW_READER, &l);
	if (err != 0)
		return (err);

	err = zap_leaf_lookup(l, zn, &zeh);
	if (err != 0)
		return (err);

	zc->zc_leaf = l;
	zc->zc_hash = zeh.zeh_hash;
	zc->zc_cd = zeh.zeh_cd;

	return (err);
}