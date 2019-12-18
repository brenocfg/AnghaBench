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
struct mgb_softc {int dummy; } ;
typedef  enum mgb_fct_cmd { ____Placeholder_mgb_fct_cmd } mgb_fct_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int,int /*<<< orphan*/ ) ; 
#define  FCT_DISABLE 130 
#define  FCT_ENABLE 129 
#define  FCT_RESET 128 
 int /*<<< orphan*/  MGB_FCT_DSBL (int) ; 
 int /*<<< orphan*/  MGB_FCT_ENBL (int) ; 
 int /*<<< orphan*/  MGB_FCT_RESET (int) ; 
 int mgb_wait_for_bits (struct mgb_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_fct_control(struct mgb_softc *sc, int reg, int channel,
    enum mgb_fct_cmd cmd)
{

	switch (cmd) {
	case FCT_RESET:
		CSR_WRITE_REG(sc, reg, MGB_FCT_RESET(channel));
		return mgb_wait_for_bits(sc, reg, 0, MGB_FCT_RESET(channel));
	case FCT_ENABLE:
		CSR_WRITE_REG(sc, reg, MGB_FCT_ENBL(channel));
		return (0);
	case FCT_DISABLE:
		CSR_WRITE_REG(sc, reg, MGB_FCT_DSBL(channel));
		return mgb_wait_for_bits(sc, reg, 0, MGB_FCT_ENBL(channel));
	}
}