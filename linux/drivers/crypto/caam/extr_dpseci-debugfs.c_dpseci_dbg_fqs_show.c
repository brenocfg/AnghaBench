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
typedef  char* u32 ;
struct seq_file {scalar_t__ private; } ;
struct dpaa2_caam_priv {int num_pairs; TYPE_2__* tx_queue_attr; TYPE_1__* rx_queue_attr; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {char* fqid; } ;
struct TYPE_3__ {char* fqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int dpaa2_io_query_fq_count (int /*<<< orphan*/ *,char*,char**,char**) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 

__attribute__((used)) static int dpseci_dbg_fqs_show(struct seq_file *file, void *offset)
{
	struct dpaa2_caam_priv *priv = (struct dpaa2_caam_priv *)file->private;
	u32 fqid, fcnt, bcnt;
	int i, err;

	seq_printf(file, "FQ stats for %s:\n", dev_name(priv->dev));
	seq_printf(file, "%s%16s%16s\n",
		   "Rx-VFQID",
		   "Pending frames",
		   "Pending bytes");

	for (i = 0; i <  priv->num_pairs; i++) {
		fqid = priv->rx_queue_attr[i].fqid;
		err = dpaa2_io_query_fq_count(NULL, fqid, &fcnt, &bcnt);
		if (err)
			continue;

		seq_printf(file, "%5d%16u%16u\n", fqid, fcnt, bcnt);
	}

	seq_printf(file, "%s%16s%16s\n",
		   "Tx-VFQID",
		   "Pending frames",
		   "Pending bytes");

	for (i = 0; i <  priv->num_pairs; i++) {
		fqid = priv->tx_queue_attr[i].fqid;
		err = dpaa2_io_query_fq_count(NULL, fqid, &fcnt, &bcnt);
		if (err)
			continue;

		seq_printf(file, "%5d%16u%16u\n", fqid, fcnt, bcnt);
	}

	return 0;
}