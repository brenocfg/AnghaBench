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
typedef  void* u32 ;
struct rss_pf_conf {int /*<<< orphan*/  rss_pf_config; void* rss_pf_mask; void* rss_pf_map; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,void*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_read_rss_pf_config (struct adapter*,int,int /*<<< orphan*/ *,int) ; 
 void* t4_read_rss_pf_map (struct adapter*,int) ; 
 void* t4_read_rss_pf_mask (struct adapter*,int) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_rss_pf_config(struct cudbg_init *pdbg_init,
				 struct cudbg_buffer *dbg_buff,
				 struct cudbg_error *cudbg_err)
{
	struct cudbg_buffer scratch_buff;
	struct rss_pf_conf *pfconf;
	struct adapter *padap = pdbg_init->adap;
	u32 rss_pf_map, rss_pf_mask, size;
	int pf, rc;

	size = 8  * sizeof(*pfconf);

	rc = get_scratch_buff(dbg_buff, size, &scratch_buff);
	if (rc)
		goto err;

	pfconf =  (struct rss_pf_conf *)scratch_buff.data;

	rss_pf_map = t4_read_rss_pf_map(padap, 1);
	rss_pf_mask = t4_read_rss_pf_mask(padap, 1);

	for (pf = 0; pf < 8; pf++) {
		pfconf[pf].rss_pf_map = rss_pf_map;
		pfconf[pf].rss_pf_mask = rss_pf_mask;
		/* no return val */
		t4_read_rss_pf_config(padap, pf, &pfconf[pf].rss_pf_config, 1);
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