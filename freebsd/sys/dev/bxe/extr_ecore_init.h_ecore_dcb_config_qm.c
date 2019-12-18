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
struct priority_cos {int /*<<< orphan*/  cos; } ;
struct bxe_softc {int dummy; } ;
typedef  enum cos_mode { ____Placeholder_cos_mode } cos_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ETH_Q ; 
 int /*<<< orphan*/  ECORE_FCOE_Q ; 
 int /*<<< orphan*/  ECORE_ISCSI_ACK_Q ; 
 int /*<<< orphan*/  ECORE_ISCSI_Q ; 
 int /*<<< orphan*/  ECORE_TOE_ACK_Q ; 
 int /*<<< orphan*/  ECORE_TOE_Q ; 
 size_t LLFC_TRAFFIC_TYPE_FCOE ; 
 size_t LLFC_TRAFFIC_TYPE_ISCSI ; 
 size_t LLFC_TRAFFIC_TYPE_NW ; 
 int STATIC_COS ; 
 int /*<<< orphan*/  ecore_map_q_cos (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ecore_dcb_config_qm(struct bxe_softc *sc, enum cos_mode mode,
				       struct priority_cos *traffic_cos)
{
	ecore_map_q_cos(sc, ECORE_FCOE_Q,
			traffic_cos[LLFC_TRAFFIC_TYPE_FCOE].cos);
	ecore_map_q_cos(sc, ECORE_ISCSI_Q,
			traffic_cos[LLFC_TRAFFIC_TYPE_ISCSI].cos);
	ecore_map_q_cos(sc, ECORE_ISCSI_ACK_Q,
		traffic_cos[LLFC_TRAFFIC_TYPE_ISCSI].cos);
	if (mode != STATIC_COS) {
		/* required only in OVERRIDE_COS mode */
		ecore_map_q_cos(sc, ECORE_ETH_Q,
				traffic_cos[LLFC_TRAFFIC_TYPE_NW].cos);
		ecore_map_q_cos(sc, ECORE_TOE_Q,
				traffic_cos[LLFC_TRAFFIC_TYPE_NW].cos);
		ecore_map_q_cos(sc, ECORE_TOE_ACK_Q,
				traffic_cos[LLFC_TRAFFIC_TYPE_NW].cos);
	}
}