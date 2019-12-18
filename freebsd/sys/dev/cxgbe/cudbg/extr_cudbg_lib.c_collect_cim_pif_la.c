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
struct cudbg_buffer {scalar_t__ data; } ;
struct cim_pif_la {int size; scalar_t__ data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CIM_PIFLA_SIZE ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_cim_read_pif_la (struct adapter*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_cim_pif_la(struct cudbg_init *pdbg_init,
			      struct cudbg_buffer *dbg_buff,
			      struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer scratch_buff;
	struct cim_pif_la *cim_pif_la_buff;
	u32 size;
	int rc = 0;

	size = sizeof(struct cim_pif_la) +
	       2 * CIM_PIFLA_SIZE * 6 * sizeof(u32);

	rc = get_scratch_buff(dbg_buff, size, &scratch_buff);
	if (rc)
		goto err;

	cim_pif_la_buff = (struct cim_pif_la *) scratch_buff.data;
	cim_pif_la_buff->size = CIM_PIFLA_SIZE;

	t4_cim_read_pif_la(padap, (u32 *)cim_pif_la_buff->data,
			   (u32 *)cim_pif_la_buff->data + 6 * CIM_PIFLA_SIZE,
			   NULL, NULL);

	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);
err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;
}