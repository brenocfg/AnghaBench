#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lzh; int /*<<< orphan*/ * active_phandle; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 

void
libbe_close(libbe_handle_t *lbh)
{

	if (lbh->active_phandle != NULL)
		zpool_close(lbh->active_phandle);
	libzfs_fini(lbh->lzh);
	free(lbh);
}