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
struct nm_bridge {int bdg_flags; scalar_t__ bdg_active_ports; int /*<<< orphan*/  bdg_saved_ops; int /*<<< orphan*/  bdg_ops; int /*<<< orphan*/  ht; int /*<<< orphan*/  bdg_basename; } ;

/* Variables and functions */
 int EBUSY ; 
 int NM_BDG_ACTIVE ; 
 int /*<<< orphan*/  NM_BNS_PUT (struct nm_bridge*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nm_os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ) ; 

int
netmap_bdg_free(struct nm_bridge *b)
{
	if ((b->bdg_flags & NM_BDG_ACTIVE) + b->bdg_active_ports != 0) {
		return EBUSY;
	}

	nm_prdis("marking bridge %s as free", b->bdg_basename);
	nm_os_free(b->ht);
	memset(&b->bdg_ops, 0, sizeof(b->bdg_ops));
	memset(&b->bdg_saved_ops, 0, sizeof(b->bdg_saved_ops));
	b->bdg_flags = 0;
	NM_BNS_PUT(b);
	return 0;
}