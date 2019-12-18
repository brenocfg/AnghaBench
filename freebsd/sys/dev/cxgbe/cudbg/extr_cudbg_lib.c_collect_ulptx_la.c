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
typedef  size_t u32 ;
struct struct_ulptx_la {void*** rd_data; void** rddata; void** wrptr; void** rdptr; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ A_ULP_TX_LA_RDDATA_0 ; 
 scalar_t__ A_ULP_TX_LA_RDPTR_0 ; 
 scalar_t__ A_ULP_TX_LA_WRPTR_0 ; 
 size_t CUDBG_NUM_ULPTX ; 
 size_t CUDBG_NUM_ULPTX_READ ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,size_t,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 void* t4_read_reg (struct adapter*,scalar_t__) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_ulptx_la(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer scratch_buff;
	struct struct_ulptx_la *ulptx_la_buff;
	u32 size, i, j;
	int rc = 0;

	size = sizeof(struct struct_ulptx_la);

	rc = get_scratch_buff(dbg_buff, size, &scratch_buff);
	if (rc)
		goto err;

	ulptx_la_buff = (struct struct_ulptx_la *) scratch_buff.data;

	for (i = 0; i < CUDBG_NUM_ULPTX; i++) {
		ulptx_la_buff->rdptr[i] = t4_read_reg(padap,
						      A_ULP_TX_LA_RDPTR_0 +
						      0x10 * i);
		ulptx_la_buff->wrptr[i] = t4_read_reg(padap,
						      A_ULP_TX_LA_WRPTR_0 +
						      0x10 * i);
		ulptx_la_buff->rddata[i] = t4_read_reg(padap,
						       A_ULP_TX_LA_RDDATA_0 +
						       0x10 * i);
		for (j = 0; j < CUDBG_NUM_ULPTX_READ; j++) {
			ulptx_la_buff->rd_data[i][j] =
				t4_read_reg(padap,
					    A_ULP_TX_LA_RDDATA_0 + 0x10 * i);
		}
	}

	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);

err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;

}