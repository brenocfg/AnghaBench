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
typedef  int u32 ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {int size; int offset; scalar_t__ data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CIM_MALA_SIZE ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_cim_read_ma_la (struct adapter*,int*,int*) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_cim_ma_la(struct cudbg_init *pdbg_init,
			     struct cudbg_buffer *dbg_buff,
			     struct cudbg_error *cudbg_err)
{
	struct cudbg_buffer scratch_buff;
	struct adapter *padap = pdbg_init->adap;
	u32 rc = 0;

	/* collect CIM MA LA */
	scratch_buff.size =  2 * CIM_MALA_SIZE * 5 * sizeof(u32);
	rc = get_scratch_buff(dbg_buff, scratch_buff.size, &scratch_buff);
	if (rc)
		goto err;

	/* no return */
	t4_cim_read_ma_la(padap,
			  (u32 *) ((char *)scratch_buff.data +
				   scratch_buff.offset),
			  (u32 *) ((char *)scratch_buff.data +
				   scratch_buff.offset + 5 * CIM_MALA_SIZE));

	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);

err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;
}