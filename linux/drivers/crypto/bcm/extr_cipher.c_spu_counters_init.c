#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num_chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  bad_icv; int /*<<< orphan*/  mb_send_fail; int /*<<< orphan*/  mb_no_spc; int /*<<< orphan*/ * aead_cnt; int /*<<< orphan*/ * hmac_cnt; int /*<<< orphan*/ * hash_cnt; int /*<<< orphan*/ ** cipher_cnt; int /*<<< orphan*/ * setkey_cnt; int /*<<< orphan*/ * op_counts; int /*<<< orphan*/  bytes_out; int /*<<< orphan*/  bytes_in; TYPE_1__ spu; int /*<<< orphan*/  next_chan; int /*<<< orphan*/  stream_count; int /*<<< orphan*/  session_count; } ;

/* Variables and functions */
 int AEAD_TYPE_LAST ; 
 int CIPHER_ALG_LAST ; 
 int CIPHER_MODE_LAST ; 
 int HASH_ALG_LAST ; 
 int SPU_OP_NUM ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ iproc_priv ; 

__attribute__((used)) static void spu_counters_init(void)
{
	int i;
	int j;

	atomic_set(&iproc_priv.session_count, 0);
	atomic_set(&iproc_priv.stream_count, 0);
	atomic_set(&iproc_priv.next_chan, (int)iproc_priv.spu.num_chan);
	atomic64_set(&iproc_priv.bytes_in, 0);
	atomic64_set(&iproc_priv.bytes_out, 0);
	for (i = 0; i < SPU_OP_NUM; i++) {
		atomic_set(&iproc_priv.op_counts[i], 0);
		atomic_set(&iproc_priv.setkey_cnt[i], 0);
	}
	for (i = 0; i < CIPHER_ALG_LAST; i++)
		for (j = 0; j < CIPHER_MODE_LAST; j++)
			atomic_set(&iproc_priv.cipher_cnt[i][j], 0);

	for (i = 0; i < HASH_ALG_LAST; i++) {
		atomic_set(&iproc_priv.hash_cnt[i], 0);
		atomic_set(&iproc_priv.hmac_cnt[i], 0);
	}
	for (i = 0; i < AEAD_TYPE_LAST; i++)
		atomic_set(&iproc_priv.aead_cnt[i], 0);

	atomic_set(&iproc_priv.mb_no_spc, 0);
	atomic_set(&iproc_priv.mb_send_fail, 0);
	atomic_set(&iproc_priv.bad_icv, 0);
}