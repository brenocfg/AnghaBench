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
typedef  scalar_t__ uint8_t ;
struct mac_configuration_hdr {int length; int /*<<< orphan*/  echo; int /*<<< orphan*/  client_id; scalar_t__ offset; } ;
struct ecore_raw_obj {int cid; } ;
struct ecore_vlan_mac_obj {struct ecore_raw_obj raw; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CPU_TO_LE16 (int) ; 
 int /*<<< orphan*/  ECORE_CPU_TO_LE32 (int) ; 
 int ECORE_SWCID_MASK ; 
 int ECORE_SWCID_SHIFT ; 

__attribute__((used)) static inline void ecore_vlan_mac_set_rdata_hdr_e1x(struct bxe_softc *sc,
	struct ecore_vlan_mac_obj *o, int type, int cam_offset,
	struct mac_configuration_hdr *hdr)
{
	struct ecore_raw_obj *r = &o->raw;

	hdr->length = 1;
	hdr->offset = (uint8_t)cam_offset;
	hdr->client_id = ECORE_CPU_TO_LE16(0xff);
	hdr->echo = ECORE_CPU_TO_LE32((r->cid & ECORE_SWCID_MASK) |
				(type << ECORE_SWCID_SHIFT));
}