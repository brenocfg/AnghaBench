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
struct struct_lb_stats {int nchan; struct lb_port_stats* s; } ;
struct lb_port_stats {int dummy; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; } ;
struct TYPE_2__ {int nports; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_get_lb_stats (struct adapter*,int,struct lb_port_stats*) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_lb_stats(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer scratch_buff;
	struct lb_port_stats *tmp_stats;
	struct struct_lb_stats *lb_stats_buff;
	u32 i, n, size;
	int rc = 0;

	rc = padap->params.nports;
	if (rc < 0)
		goto err;

	n = rc;
	size = sizeof(struct struct_lb_stats) +
	       n * sizeof(struct lb_port_stats);

	rc = get_scratch_buff(dbg_buff, size, &scratch_buff);
	if (rc)
		goto err;

	lb_stats_buff = (struct struct_lb_stats *) scratch_buff.data;

	lb_stats_buff->nchan = n;
	tmp_stats = lb_stats_buff->s;

	for (i = 0; i < n; i += 2, tmp_stats += 2) {
		t4_get_lb_stats(padap, i, tmp_stats);
		t4_get_lb_stats(padap, i + 1, tmp_stats+1);
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