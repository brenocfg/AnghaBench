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
typedef  int uint8_t ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct elink_ets_params {int dummy; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P0 ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P1 ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P0 ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P1 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static elink_status_t elink_ets_e3b0_cli_map(const struct elink_params *params,
				  const struct elink_ets_params *ets_params,
				  const uint8_t cos_sp_bitmap,
				  const uint8_t cos_bw_bitmap)
{
	struct bxe_softc *sc = params->sc;
	const uint8_t port = params->port;
	const uint8_t nig_cli_sp_bitmap = 0x7 | (cos_sp_bitmap << 3);
	const uint8_t pbf_cli_sp_bitmap = cos_sp_bitmap;
	const uint8_t nig_cli_subject2wfq_bitmap = cos_bw_bitmap << 3;
	const uint8_t pbf_cli_subject2wfq_bitmap = cos_bw_bitmap;

	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT :
	       NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, nig_cli_sp_bitmap);

	REG_WR(sc, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P1 :
	       PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P0 , pbf_cli_sp_bitmap);

	REG_WR(sc, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ :
	       NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ,
	       nig_cli_subject2wfq_bitmap);

	REG_WR(sc, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P1 :
	       PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P0,
	       pbf_cli_subject2wfq_bitmap);

	return ELINK_STATUS_OK;
}