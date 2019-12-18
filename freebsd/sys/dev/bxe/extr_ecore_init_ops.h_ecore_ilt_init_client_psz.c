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
typedef  int /*<<< orphan*/  uint32_t ;
struct ilt_client_info {int flags; int page_size; } ;
struct ecore_ilt {struct ilt_client_info* clients; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILOG2 (int) ; 
 int ILT_CLIENT_SKIP_INIT ; 
#define  INITOP_CLEAR 130 
#define  INITOP_INIT 129 
#define  INITOP_SET 128 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ecore_ilt* SC_ILT (struct bxe_softc*) ; 

__attribute__((used)) static void ecore_ilt_init_client_psz(struct bxe_softc *sc, int cli_num,
				      uint32_t psz_reg, uint8_t initop)
{
	struct ecore_ilt *ilt = SC_ILT(sc);
	struct ilt_client_info *ilt_cli = &ilt->clients[cli_num];

	if (ilt_cli->flags & ILT_CLIENT_SKIP_INIT)
		return;

	switch (initop) {
	case INITOP_INIT:
		/* set in the init-value array */
	case INITOP_SET:
		REG_WR(sc, psz_reg, ILOG2(ilt_cli->page_size >> 12));
		break;
	case INITOP_CLEAR:
		break;
	}
}