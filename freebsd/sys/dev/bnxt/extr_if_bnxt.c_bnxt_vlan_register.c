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
typedef  int /*<<< orphan*/  uint16_t ;
struct bnxt_vlan_tag {int tpid; int /*<<< orphan*/  tag; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan_tags; } ;
struct bnxt_softc {TYPE_1__ vnic_info; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bnxt_vlan_tag*,int /*<<< orphan*/ ) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 struct bnxt_vlan_tag* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
bnxt_vlan_register(if_ctx_t ctx, uint16_t vtag)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	struct bnxt_vlan_tag *new_tag;

	new_tag = malloc(sizeof(struct bnxt_vlan_tag), M_DEVBUF, M_NOWAIT);
	if (new_tag == NULL)
		return;
	new_tag->tag = vtag;
	new_tag->tpid = 8100;
	SLIST_INSERT_HEAD(&softc->vnic_info.vlan_tags, new_tag, next);
}