#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * zv_objset; } ;
typedef  TYPE_2__ zvol_state_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {int lrc_reclen; } ;
struct TYPE_7__ {int lr_offset; int lr_length; int /*<<< orphan*/  lr_blkptr; TYPE_1__ lr_common; } ;
typedef  TYPE_3__ lr_write_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int BP_GET_LSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dmu_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zvol_replay_write(void *arg1, void *arg2, boolean_t byteswap)
{
	zvol_state_t *zv = arg1;
	lr_write_t *lr = arg2;
	objset_t *os = zv->zv_objset;
	char *data = (char *)(lr + 1);	/* data follows lr_write_t */
	uint64_t offset, length;
	dmu_tx_t *tx;
	int error;

	if (byteswap)
		byteswap_uint64_array(lr, sizeof (*lr));

	offset = lr->lr_offset;
	length = lr->lr_length;

	/* If it's a dmu_sync() block, write the whole block */
	if (lr->lr_common.lrc_reclen == sizeof (lr_write_t)) {
		uint64_t blocksize = BP_GET_LSIZE(&lr->lr_blkptr);
		if (length < blocksize) {
			offset -= offset % blocksize;
			length = blocksize;
		}
	}

	tx = dmu_tx_create(os);
	dmu_tx_hold_write(tx, ZVOL_OBJ, offset, length);
	error = dmu_tx_assign(tx, TXG_WAIT);
	if (error) {
		dmu_tx_abort(tx);
	} else {
		dmu_write(os, ZVOL_OBJ, offset, length, data, tx);
		dmu_tx_commit(tx);
	}

	return (error);
}