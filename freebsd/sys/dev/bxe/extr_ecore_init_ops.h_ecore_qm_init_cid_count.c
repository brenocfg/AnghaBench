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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
#define  INITOP_CLEAR 130 
#define  INITOP_INIT 129 
#define  INITOP_SET 128 
 scalar_t__ QM_INIT (int) ; 
 int /*<<< orphan*/  QM_REG_CONNNUM_0 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int SC_PORT (struct bxe_softc*) ; 

__attribute__((used)) static void ecore_qm_init_cid_count(struct bxe_softc *sc, int qm_cid_count,
				    uint8_t initop)
{
	int port = SC_PORT(sc);

	if (QM_INIT(qm_cid_count)) {
		switch (initop) {
		case INITOP_INIT:
			/* set in the init-value array */
		case INITOP_SET:
			REG_WR(sc, QM_REG_CONNNUM_0 + port*4,
			       qm_cid_count/16 - 1);
			break;
		case INITOP_CLEAR:
			break;
		}
	}
}