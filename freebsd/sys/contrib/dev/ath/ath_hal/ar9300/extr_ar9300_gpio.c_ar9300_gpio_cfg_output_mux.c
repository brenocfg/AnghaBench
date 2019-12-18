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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIO_OUTPUT_MUX1 ; 
 int /*<<< orphan*/  AR_GPIO_OUTPUT_MUX2 ; 
 int /*<<< orphan*/  AR_GPIO_OUTPUT_MUX3 ; 
 int AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int,int,int) ; 

__attribute__((used)) static void
ar9300_gpio_cfg_output_mux(struct ath_hal *ah, u_int32_t gpio, u_int32_t type)
{
    int          addr;
    u_int32_t    gpio_shift;

    /* each MUX controls 6 GPIO pins */
    if (gpio > 11) {
        addr = AR_HOSTIF_REG(ah, AR_GPIO_OUTPUT_MUX3);
    } else if (gpio > 5) {
        addr = AR_HOSTIF_REG(ah, AR_GPIO_OUTPUT_MUX2);
    } else {
        addr = AR_HOSTIF_REG(ah, AR_GPIO_OUTPUT_MUX1);
    }

    /*
     * 5 bits per GPIO pin.
     * Bits 0..4 for 1st pin in that mux,
     * bits 5..9 for 2nd pin, etc.
     */
    gpio_shift = (gpio % 6) * 5;

    OS_REG_RMW(ah, addr, (type << gpio_shift), (0x1f << gpio_shift));
}