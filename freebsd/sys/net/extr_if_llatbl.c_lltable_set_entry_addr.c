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
struct llentry {size_t r_hdrlen; int /*<<< orphan*/  r_flags; int /*<<< orphan*/  la_flags; int /*<<< orphan*/ * r_linkdata; int /*<<< orphan*/ * ll_addr; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLE_VALID ; 
 int /*<<< orphan*/  RLLE_VALID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 

void
lltable_set_entry_addr(struct ifnet *ifp, struct llentry *lle,
    const char *linkhdr, size_t linkhdrsize, int lladdr_off)
{

	memcpy(lle->r_linkdata, linkhdr, linkhdrsize);
	lle->r_hdrlen = linkhdrsize;
	lle->ll_addr = &lle->r_linkdata[lladdr_off];
	lle->la_flags |= LLE_VALID;
	lle->r_flags |= RLLE_VALID;
}