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
typedef  void* uint8_t ;
struct TYPE_3__ {void* length; int /*<<< orphan*/  echo; int /*<<< orphan*/  client_id; void* offset; } ;
struct mac_configuration_cmd {TYPE_1__ hdr; } ;
struct ecore_raw_obj {int func_id; int cid; scalar_t__ rdata; } ;
struct ecore_mcast_ramrod_params {TYPE_2__* mcast_obj; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_4__ {struct ecore_raw_obj raw; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_CPU_TO_LE16 (int) ; 
 int /*<<< orphan*/  ECORE_CPU_TO_LE32 (int) ; 
 int ECORE_FILTER_MCAST_PENDING ; 
 int ECORE_MAX_EMUL_MULTI ; 
 int ECORE_MAX_MULTICAST ; 
 int ECORE_SWCID_MASK ; 
 int ECORE_SWCID_SHIFT ; 

__attribute__((used)) static inline void ecore_mcast_set_rdata_hdr_e1(struct bxe_softc *sc,
					struct ecore_mcast_ramrod_params *p,
					uint8_t len)
{
	struct ecore_raw_obj *r = &p->mcast_obj->raw;
	struct mac_configuration_cmd *data =
		(struct mac_configuration_cmd *)(r->rdata);

	uint8_t offset = (CHIP_REV_IS_SLOW(sc) ?
		     ECORE_MAX_EMUL_MULTI*(1 + r->func_id) :
		     ECORE_MAX_MULTICAST*(1 + r->func_id));

	data->hdr.offset = offset;
	data->hdr.client_id = ECORE_CPU_TO_LE16(0xff);
	data->hdr.echo = ECORE_CPU_TO_LE32((r->cid & ECORE_SWCID_MASK) |
				     (ECORE_FILTER_MCAST_PENDING <<
				      ECORE_SWCID_SHIFT));
	data->hdr.length = len;
}