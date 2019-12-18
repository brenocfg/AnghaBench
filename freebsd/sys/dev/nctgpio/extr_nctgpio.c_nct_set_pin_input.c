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
typedef  int /*<<< orphan*/  uint32_t ;
struct nct_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IOR ; 
 int /*<<< orphan*/  nct_set_pin_reg (struct nct_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nct_set_pin_input(struct nct_softc *sc, uint32_t pin_num, bool val)
{
	nct_set_pin_reg(sc, REG_IOR, pin_num, val);
}