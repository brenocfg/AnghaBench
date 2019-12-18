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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  rule_cnt; int /*<<< orphan*/  echo; } ;
struct eth_multicast_rules_ramrod_data {TYPE_2__ header; } ;
struct ecore_raw_obj {int cid; scalar_t__ rdata; } ;
struct ecore_mcast_ramrod_params {TYPE_1__* mcast_obj; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_3__ {struct ecore_raw_obj raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CPU_TO_LE32 (int) ; 
 int ECORE_FILTER_MCAST_PENDING ; 
 int ECORE_SWCID_MASK ; 
 int ECORE_SWCID_SHIFT ; 

__attribute__((used)) static inline void ecore_mcast_set_rdata_hdr_e2(struct bxe_softc *sc,
					struct ecore_mcast_ramrod_params *p,
					uint8_t len)
{
	struct ecore_raw_obj *r = &p->mcast_obj->raw;
	struct eth_multicast_rules_ramrod_data *data =
		(struct eth_multicast_rules_ramrod_data *)(r->rdata);

	data->header.echo = ECORE_CPU_TO_LE32((r->cid & ECORE_SWCID_MASK) |
					(ECORE_FILTER_MCAST_PENDING <<
					 ECORE_SWCID_SHIFT));
	data->header.rule_cnt = len;
}