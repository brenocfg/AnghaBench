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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  DBG_PHY ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_GPIO ; 
 int MISC_REGISTERS_GPIO_3 ; 
 int MISC_REGISTERS_GPIO_INT_CLR_POS ; 
#define  MISC_REGISTERS_GPIO_INT_OUTPUT_CLR 129 
#define  MISC_REGISTERS_GPIO_INT_OUTPUT_SET 128 
 int MISC_REGISTERS_GPIO_INT_SET_POS ; 
 int MISC_REGISTERS_GPIO_PORT_SHIFT ; 
 int /*<<< orphan*/  MISC_REG_GPIO_INT ; 
 int /*<<< orphan*/  NIG_REG_PORT_SWAP ; 
 int /*<<< orphan*/  NIG_REG_STRAP_OVERRIDE ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bxe_acquire_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_gpio_int_write(struct bxe_softc *sc,
                   int              gpio_num,
                   uint32_t         mode,
                   uint8_t          port)
{
    /* The GPIO should be swapped if swap register is set and active */
    int gpio_port = ((REG_RD(sc, NIG_REG_PORT_SWAP) &&
                      REG_RD(sc, NIG_REG_STRAP_OVERRIDE)) ^ port);
    int gpio_shift = (gpio_num +
                      (gpio_port ? MISC_REGISTERS_GPIO_PORT_SHIFT : 0));
    uint32_t gpio_mask = (1 << gpio_shift);
    uint32_t gpio_reg;

    if (gpio_num > MISC_REGISTERS_GPIO_3) {
        BLOGE(sc, "Invalid GPIO %d mode 0x%x port 0x%x gpio_port %d"
            " gpio_shift %d gpio_mask 0x%x\n",
            gpio_num, mode, port, gpio_port, gpio_shift, gpio_mask);
        return (-1);
    }

    bxe_acquire_hw_lock(sc, HW_LOCK_RESOURCE_GPIO);

    /* read GPIO int */
    gpio_reg = REG_RD(sc, MISC_REG_GPIO_INT);

    switch (mode) {
    case MISC_REGISTERS_GPIO_INT_OUTPUT_CLR:
        BLOGD(sc, DBG_PHY,
              "Clear GPIO INT %d (shift %d) -> output low\n",
              gpio_num, gpio_shift);
        /* clear SET and set CLR */
        gpio_reg &= ~(gpio_mask << MISC_REGISTERS_GPIO_INT_SET_POS);
        gpio_reg |=  (gpio_mask << MISC_REGISTERS_GPIO_INT_CLR_POS);
        break;

    case MISC_REGISTERS_GPIO_INT_OUTPUT_SET:
        BLOGD(sc, DBG_PHY,
              "Set GPIO INT %d (shift %d) -> output high\n",
              gpio_num, gpio_shift);
        /* clear CLR and set SET */
        gpio_reg &= ~(gpio_mask << MISC_REGISTERS_GPIO_INT_CLR_POS);
        gpio_reg |=  (gpio_mask << MISC_REGISTERS_GPIO_INT_SET_POS);
        break;

    default:
        break;
    }

    REG_WR(sc, MISC_REG_GPIO_INT, gpio_reg);
    bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_GPIO);

    return (0);
}