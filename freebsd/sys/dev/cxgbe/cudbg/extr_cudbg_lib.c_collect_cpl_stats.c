#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct struct_tp_cpl_stats {int /*<<< orphan*/  stats; int /*<<< orphan*/  nchan; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; } ;
struct adapter {TYPE_1__* chip_params; } ;
struct TYPE_2__ {int /*<<< orphan*/  nchan; } ;

/* Variables and functions */
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_tp_get_cpl_stats (struct adapter*,int /*<<< orphan*/ *,int) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_cpl_stats(struct cudbg_init *pdbg_init,
			     struct cudbg_buffer *dbg_buff,
			     struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer scratch_buff;
	struct struct_tp_cpl_stats *tp_cpl_stats_buff;
	u32 size;
	int rc = 0;

	size = sizeof(struct struct_tp_cpl_stats);

	rc = get_scratch_buff(dbg_buff, size, &scratch_buff);
	if (rc)
		goto err;

	tp_cpl_stats_buff = (struct struct_tp_cpl_stats *) scratch_buff.data;
	tp_cpl_stats_buff->nchan = padap->chip_params->nchan;

	/* spin_lock(&padap->stats_lock);	TODO*/
	t4_tp_get_cpl_stats(padap, &tp_cpl_stats_buff->stats, 1);
	/* spin_unlock(&padap->stats_lock);	TODO*/

	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);

err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;
}