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
struct device_map_entry {struct device_map_entry* location_key; struct device_map_entry* name_key; int /*<<< orphan*/ * entry_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_DEV_STRUCT (int /*<<< orphan*/ *) ; 
 struct device_map_entry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * devd_fd ; 
 int devd_sock ; 
 int /*<<< orphan*/  device_map ; 
 int /*<<< orphan*/  device_tbl ; 
 int /*<<< orphan*/  devinfo_free () ; 
 int /*<<< orphan*/  fd_deselect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct device_map_entry*) ; 
 int /*<<< orphan*/  link ; 

void
fini_device_tbl(void)
{
	struct device_map_entry *n1;

	if (devd_fd != NULL)
		fd_deselect(devd_fd);

	if (devd_sock != -1)
		(void)close(devd_sock);

	devinfo_free();

     	while ((n1 = STAILQ_FIRST(&device_map)) != NULL) {
		STAILQ_REMOVE_HEAD(&device_map, link);
		if (n1->entry_p != NULL) {
			TAILQ_REMOVE(&device_tbl, n1->entry_p, link);
			FREE_DEV_STRUCT(n1->entry_p);
		}
		free(n1->name_key);
		free(n1->location_key);
		free(n1);
     	}
	assert(TAILQ_EMPTY(&device_tbl));
}