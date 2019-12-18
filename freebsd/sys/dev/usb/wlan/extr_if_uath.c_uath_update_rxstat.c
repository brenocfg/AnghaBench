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
typedef  int uint32_t ;
struct uath_softc {int dummy; } ;

/* Variables and functions */
#define  UATH_STATUS_CRC_ERR 135 
#define  UATH_STATUS_DECOMP_ERR 134 
#define  UATH_STATUS_DECRYPT_CRC_ERR 133 
#define  UATH_STATUS_DECRYPT_MIC_ERR 132 
#define  UATH_STATUS_ERR 131 
#define  UATH_STATUS_KEY_ERR 130 
#define  UATH_STATUS_PHY_ERR 129 
#define  UATH_STATUS_STOP_IN_PROGRESS 128 
 int /*<<< orphan*/  UATH_STAT_INC (struct uath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_crcerr ; 
 int /*<<< orphan*/  st_decomperr ; 
 int /*<<< orphan*/  st_decrypt_crcerr ; 
 int /*<<< orphan*/  st_decrypt_micerr ; 
 int /*<<< orphan*/  st_err ; 
 int /*<<< orphan*/  st_keyerr ; 
 int /*<<< orphan*/  st_phyerr ; 
 int /*<<< orphan*/  st_stopinprogress ; 

__attribute__((used)) static void
uath_update_rxstat(struct uath_softc *sc, uint32_t status)
{

	switch (status) {
	case UATH_STATUS_STOP_IN_PROGRESS:
		UATH_STAT_INC(sc, st_stopinprogress);
		break;
	case UATH_STATUS_CRC_ERR:
		UATH_STAT_INC(sc, st_crcerr);
		break;
	case UATH_STATUS_PHY_ERR:
		UATH_STAT_INC(sc, st_phyerr);
		break;
	case UATH_STATUS_DECRYPT_CRC_ERR:
		UATH_STAT_INC(sc, st_decrypt_crcerr);
		break;
	case UATH_STATUS_DECRYPT_MIC_ERR:
		UATH_STAT_INC(sc, st_decrypt_micerr);
		break;
	case UATH_STATUS_DECOMP_ERR:
		UATH_STAT_INC(sc, st_decomperr);
		break;
	case UATH_STATUS_KEY_ERR:
		UATH_STAT_INC(sc, st_keyerr);
		break;
	case UATH_STATUS_ERR:
		UATH_STAT_INC(sc, st_err);
		break;
	default:
		break;
	}
}