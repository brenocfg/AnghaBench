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
struct fsi_master {int n_links; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int fsi_master_break (struct fsi_master*,int) ; 
 int fsi_master_link_enable (struct fsi_master*,int) ; 
 int /*<<< orphan*/  fsi_slave_init (struct fsi_master*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_master_scan(struct fsi_master *master)
{
	int link, rc;

	for (link = 0; link < master->n_links; link++) {
		rc = fsi_master_link_enable(master, link);
		if (rc) {
			dev_dbg(&master->dev,
				"enable link %d failed: %d\n", link, rc);
			continue;
		}
		rc = fsi_master_break(master, link);
		if (rc) {
			dev_dbg(&master->dev,
				"break to link %d failed: %d\n", link, rc);
			continue;
		}

		fsi_slave_init(master, link, 0);
	}

	return 0;
}