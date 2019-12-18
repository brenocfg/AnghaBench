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
struct disk_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 struct disk_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct disk_entry*,int /*<<< orphan*/ ) ; 
 int close (int) ; 
 struct disk_entry* disk_list ; 
 int /*<<< orphan*/  disk_tbl ; 
 int /*<<< orphan*/  free (struct disk_entry*) ; 
 int /*<<< orphan*/  link ; 
 int md_fd ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void
fini_disk_storage_tbl(void)
{
	struct disk_entry *n1;

	while ((n1 = TAILQ_FIRST(&disk_tbl)) != NULL) {
		TAILQ_REMOVE(&disk_tbl, n1, link);
		free(n1);
	}

	free(disk_list);

	if (md_fd > 0) {
		if (close(md_fd) == -1)
			syslog(LOG_ERR,"close (/dev/mdctl) failed: %m");
		md_fd = -1;
	}
}