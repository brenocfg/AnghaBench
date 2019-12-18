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
struct cudbg_pbt_tables {int /*<<< orphan*/ * pbt_data; int /*<<< orphan*/ * lrf_table; int /*<<< orphan*/ * pbt_static; int /*<<< orphan*/ * pbt_dynamic; } ;
struct cudbg_init {int /*<<< orphan*/  (* print ) (char*) ;scalar_t__ verbose; struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {int size; scalar_t__ data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CUDBG_CHAC_PBT_ADDR ; 
 int CUDBG_CHAC_PBT_DATA ; 
 int CUDBG_CHAC_PBT_LRF ; 
 int CUDBG_LRF_ENTRIES ; 
 int CUDBG_PBT_DATA_ENTRIES ; 
 int CUDBG_PBT_DYNAMIC_ENTRIES ; 
 int CUDBG_PBT_STATIC_ENTRIES ; 
 int cim_ha_rreg (struct adapter*,int,int /*<<< orphan*/ *) ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 
 int /*<<< orphan*/  stub3 (char*) ; 
 int /*<<< orphan*/  stub4 (char*) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_pbt_tables(struct cudbg_init *pdbg_init,
			      struct cudbg_buffer *dbg_buff,
			      struct cudbg_error *cudbg_err)
{
	struct cudbg_buffer scratch_buff;
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_pbt_tables *pbt = NULL;
	u32 size;
	u32 addr;
	int i, rc;

	size = sizeof(struct cudbg_pbt_tables);
	scratch_buff.size = size;

	rc = get_scratch_buff(dbg_buff, scratch_buff.size, &scratch_buff);
	if (rc)
		goto err;

	pbt = (struct cudbg_pbt_tables *)scratch_buff.data;

	/* PBT dynamic entries */
	addr = CUDBG_CHAC_PBT_ADDR;
	for (i = 0; i < CUDBG_PBT_DYNAMIC_ENTRIES; i++) {
		rc = cim_ha_rreg(padap, addr + (i * 4), &pbt->pbt_dynamic[i]);
		if (rc) {
			if (pdbg_init->verbose)
				pdbg_init->print("BUSY timeout reading"
					 "CIM_HOST_ACC_CTRL\n");
			goto err1;
		}
	}

	/* PBT static entries */

	/* static entries start when bit 6 is set */
	addr = CUDBG_CHAC_PBT_ADDR + (1 << 6);
	for (i = 0; i < CUDBG_PBT_STATIC_ENTRIES; i++) {
		rc = cim_ha_rreg(padap, addr + (i * 4), &pbt->pbt_static[i]);
		if (rc) {
			if (pdbg_init->verbose)
				pdbg_init->print("BUSY timeout reading"
					 "CIM_HOST_ACC_CTRL\n");
			goto err1;
		}
	}

	/* LRF entries */
	addr = CUDBG_CHAC_PBT_LRF;
	for (i = 0; i < CUDBG_LRF_ENTRIES; i++) {
		rc = cim_ha_rreg(padap, addr + (i * 4), &pbt->lrf_table[i]);
		if (rc) {
			if (pdbg_init->verbose)
				pdbg_init->print("BUSY timeout reading"
					 "CIM_HOST_ACC_CTRL\n");
			goto err1;
		}
	}

	/* PBT data entries */
	addr = CUDBG_CHAC_PBT_DATA;
	for (i = 0; i < CUDBG_PBT_DATA_ENTRIES; i++) {
		rc = cim_ha_rreg(padap, addr + (i * 4), &pbt->pbt_data[i]);
		if (rc) {
			if (pdbg_init->verbose)
				pdbg_init->print("BUSY timeout reading"
					 "CIM_HOST_ACC_CTRL\n");
			goto err1;
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