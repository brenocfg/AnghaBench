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
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,int) ; 
 int /*<<< orphan*/  DBG_PHY ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_GPIO ; 
 int MISC_REGISTERS_GPIO_CLR_POS ; 
 int MISC_REGISTERS_GPIO_FLOAT_POS ; 
#define  MISC_REGISTERS_GPIO_INPUT_HI_Z 130 
#define  MISC_REGISTERS_GPIO_OUTPUT_HIGH 129 
#define  MISC_REGISTERS_GPIO_OUTPUT_LOW 128 
 int MISC_REGISTERS_GPIO_SET_POS ; 
 int /*<<< orphan*/  MISC_REG_GPIO ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bxe_acquire_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_gpio_mult_write(struct bxe_softc *sc,
                    uint8_t          pins,
                    uint32_t         mode)
{
    uint32_t gpio_reg;

    /* any port swapping should be handled by caller */

    bxe_acquire_hw_lock(sc, HW_LOCK_RESOURCE_GPIO);

    /* read GPIO and mask except the float bits */
    gpio_reg = REG_RD(sc, MISC_REG_GPIO);
    gpio_reg &= ~(pins << MISC_REGISTERS_GPIO_FLOAT_POS);
    gpio_reg &= ~(pins << MISC_REGISTERS_GPIO_CLR_POS);
    gpio_reg &= ~(pins << MISC_REGISTERS_GPIO_SET_POS);

    switch (mode) {
    case MISC_REGISTERS_GPIO_OUTPUT_LOW:
        BLOGD(sc, DBG_PHY, "Set GPIO 0x%x -> output low\n", pins);
        /* set CLR */
        gpio_reg |= (pins << MISC_REGISTERS_GPIO_CLR_POS);
        break;

    case MISC_REGISTERS_GPIO_OUTPUT_HIGH:
        BLOGD(sc, DBG_PHY, "Set GPIO 0x%x -> output high\n", pins);
        /* set SET */
        gpio_reg |= (pins << MISC_REGISTERS_GPIO_SET_POS);
        break;

    case MISC_REGISTERS_GPIO_INPUT_HI_Z:
        BLOGD(sc, DBG_PHY, "Set GPIO 0x%x -> input\n", pins);
        /* set FLOAT */
        gpio_reg |= (pins << MISC_REGISTERS_GPIO_FLOAT_POS);
        break;

    default:
        BLOGE(sc, "Invalid GPIO mode assignment pins 0x%x mode 0x%x"
            " gpio_reg 0x%x\n", pins, mode, gpio_reg);
        bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_GPIO);
        return (-1);
    }

    REG_WR(sc, MISC_REG_GPIO, gpio_reg);
    bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_GPIO);

    return (0);
}