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
struct ixl_vsi {int /*<<< orphan*/  ftl; } ;
struct ixl_mac_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct ixl_mac_filter* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ixl_mac_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

void
ixl_free_mac_filters(struct ixl_vsi *vsi)
{
	struct ixl_mac_filter *f;

	while (!SLIST_EMPTY(&vsi->ftl)) {
		f = SLIST_FIRST(&vsi->ftl);
		SLIST_REMOVE_HEAD(&vsi->ftl, next);
		free(f, M_DEVBUF);
	}
}