#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int halNumGpioPins; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;
typedef  size_t HAL_GPIO_MUX_TYPE ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int AR9382_GPIO_9_INPUT_ONLY ; 
 int AR9382_GPIO_PIN_8_RESERVED ; 
 int AR9382_MAX_JTAG_GPIO_PIN_NUM ; 
 int ARRAY_LENGTH (int const*) ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_EN_VAL ; 
 int /*<<< orphan*/  AR_GPIO_JTAG_DISABLE ; 
 int /*<<< orphan*/  AR_GPIO_OE_OUT ; 
 int AR_GPIO_OE_OUT_DRV ; 
 int AR_GPIO_OE_OUT_DRV_ALL ; 
#define  AR_GPIO_OUTPUT_MUX_AS_BT_IN_RX 148 
#define  AR_GPIO_OUTPUT_MUX_AS_BT_IN_TX 147 
#define  AR_GPIO_OUTPUT_MUX_AS_MAC_NETWORK_LED 146 
#define  AR_GPIO_OUTPUT_MUX_AS_MAC_POWER_LED 145 
#define  AR_GPIO_OUTPUT_MUX_AS_MCI_BT_CLK 144 
#define  AR_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA 143 
#define  AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_CLK 142 
#define  AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_DATA 141 
#define  AR_GPIO_OUTPUT_MUX_AS_OUTPUT 140 
#define  AR_GPIO_OUTPUT_MUX_AS_PCIE_ATTENTION_LED 139 
#define  AR_GPIO_OUTPUT_MUX_AS_PCIE_POWER_LED 138 
#define  AR_GPIO_OUTPUT_MUX_AS_RUCKUS_DATA 137 
#define  AR_GPIO_OUTPUT_MUX_AS_RUCKUS_STROBE 136 
#define  AR_GPIO_OUTPUT_MUX_AS_RX_CLEAR_EXTERNAL 135 
#define  AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL0 134 
#define  AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL1 133 
#define  AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL2 132 
#define  AR_GPIO_OUTPUT_MUX_AS_SWCOM3 131 
#define  AR_GPIO_OUTPUT_MUX_AS_TX_FRAME 130 
#define  AR_GPIO_OUTPUT_MUX_AS_WL_IN_RX 129 
#define  AR_GPIO_OUTPUT_MUX_AS_WL_IN_TX 128 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int ATH_GPIOFUNC_ANTCHAIN0 ; 
 int ATH_GPIOFUNC_ANTCHAIN1 ; 
 int ATH_GPIOFUNC_ANTCHAIN2 ; 
 int ATH_GPIOFUNC_ROUTE_SWCOM3 ; 
 int ATH_GPIOPIN_ANTCHAIN0 ; 
 int ATH_GPIOPIN_ANTCHAIN1 ; 
 int ATH_GPIOPIN_ANTCHAIN2 ; 
 int ATH_GPIOPIN_ROUTE_SWCOM3 ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_gpio_cfg_output_mux (struct ath_hal*,int,int) ; 
 int /*<<< orphan*/  ar9340_soc_gpio_cfg_output_mux (struct ath_hal*,int,int) ; 

HAL_BOOL
ar9300_gpio_cfg_output(
    struct ath_hal *ah,
    u_int32_t gpio,
    HAL_GPIO_MUX_TYPE hal_signal_type)
{
    u_int32_t    ah_signal_type;
    u_int32_t    gpio_shift;
    u_int8_t    smart_ant = 0;
    static const u_int32_t    mux_signal_conversion_table[] = {
                    /* HAL_GPIO_OUTPUT_MUX_AS_OUTPUT             */
        AR_GPIO_OUTPUT_MUX_AS_OUTPUT,
                    /* HAL_GPIO_OUTPUT_MUX_AS_PCIE_ATTENTION_LED */
        AR_GPIO_OUTPUT_MUX_AS_PCIE_ATTENTION_LED,
                    /* HAL_GPIO_OUTPUT_MUX_AS_PCIE_POWER_LED     */
        AR_GPIO_OUTPUT_MUX_AS_PCIE_POWER_LED,
                    /* HAL_GPIO_OUTPUT_MUX_AS_MAC_NETWORK_LED    */
        AR_GPIO_OUTPUT_MUX_AS_MAC_NETWORK_LED,
                    /* HAL_GPIO_OUTPUT_MUX_AS_MAC_POWER_LED      */
        AR_GPIO_OUTPUT_MUX_AS_MAC_POWER_LED,
                    /* HAL_GPIO_OUTPUT_MUX_AS_WLAN_ACTIVE        */
        AR_GPIO_OUTPUT_MUX_AS_RX_CLEAR_EXTERNAL,
                    /* HAL_GPIO_OUTPUT_MUX_AS_TX_FRAME           */
        AR_GPIO_OUTPUT_MUX_AS_TX_FRAME,
                    /* HAL_GPIO_OUTPUT_MUX_AS_MCI_WLAN_DATA      */
        AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_DATA,
                    /* HAL_GPIO_OUTPUT_MUX_AS_MCI_WLAN_CLK       */
        AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_CLK,
                    /* HAL_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA        */
        AR_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA,
                    /* HAL_GPIO_OUTPUT_MUX_AS_MCI_BT_CLK         */
        AR_GPIO_OUTPUT_MUX_AS_MCI_BT_CLK,
	            /* HAL_GPIO_OUTPUT_MUX_AS_WL_IN_TX           */
        AR_GPIO_OUTPUT_MUX_AS_WL_IN_TX,
                    /* HAL_GPIO_OUTPUT_MUX_AS_WL_IN_RX           */
        AR_GPIO_OUTPUT_MUX_AS_WL_IN_RX,
                    /* HAL_GPIO_OUTPUT_MUX_AS_BT_IN_TX           */
        AR_GPIO_OUTPUT_MUX_AS_BT_IN_TX,
                    /* HAL_GPIO_OUTPUT_MUX_AS_BT_IN_RX           */
        AR_GPIO_OUTPUT_MUX_AS_BT_IN_RX,
                    /* HAL_GPIO_OUTPUT_MUX_AS_RUCKUS_STROBE      */
        AR_GPIO_OUTPUT_MUX_AS_RUCKUS_STROBE,
                    /* HAL_GPIO_OUTPUT_MUX_AS_RUCKUS_DATA        */
        AR_GPIO_OUTPUT_MUX_AS_RUCKUS_DATA,
                    /* HAL_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL0     */
        AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL0,
                    /* HAL_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL1     */
        AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL1,
                    /* HAL_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL2     */
        AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL2,
                    /* HAL_GPIO_OUTPUT_MUX_AS_SMARTANT_SWCOM3    */
        AR_GPIO_OUTPUT_MUX_AS_SWCOM3,
    };

    HALASSERT(gpio < AH_PRIVATE(ah)->ah_caps.halNumGpioPins);
    if ((gpio == AR9382_GPIO_PIN_8_RESERVED)  ||
        (gpio == AR9382_GPIO_9_INPUT_ONLY))
    {
        return AH_FALSE;
    }

    /* Convert HAL signal type definitions to hardware-specific values. */
    if ((int) hal_signal_type < ARRAY_LENGTH(mux_signal_conversion_table))
    {
        ah_signal_type = mux_signal_conversion_table[hal_signal_type];
    } else {
        return AH_FALSE;
    }

    if (gpio <= AR9382_MAX_JTAG_GPIO_PIN_NUM) {
        OS_REG_SET_BIT(ah,
            AR_HOSTIF_REG(ah, AR_GPIO_INPUT_EN_VAL), AR_GPIO_JTAG_DISABLE);
    }

#if UMAC_SUPPORT_SMARTANTENNA
    /* Get the pin and func values for smart antenna */
    switch (ah_signal_type)
    {
        case AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL0:
            gpio = ATH_GPIOPIN_ANTCHAIN0;
            ah_signal_type = ATH_GPIOFUNC_ANTCHAIN0;
            smart_ant = 1;
            break; 
        case AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL1:
            gpio = ATH_GPIOPIN_ANTCHAIN1;
            ah_signal_type = ATH_GPIOFUNC_ANTCHAIN1;
            smart_ant = 1;
            break;
        case AR_GPIO_OUTPUT_MUX_AS_SMARTANT_CTRL2:    
            gpio = ATH_GPIOPIN_ANTCHAIN2;
            ah_signal_type = ATH_GPIOFUNC_ANTCHAIN2;
            smart_ant = 1;
            break;
#if ATH_SMARTANTENNA_ROUTE_SWCOM_TO_GPIO
        case AR_GPIO_OUTPUT_MUX_AS_SWCOM3:
            gpio = ATH_GPIOPIN_ROUTE_SWCOM3;
            ah_signal_type = ATH_GPIOFUNC_ROUTE_SWCOM3;
            smart_ant = 1;
            break;
#endif
        default:
            break;
    }
#endif

    if (smart_ant && (AR_SREV_WASP(ah) || AR_SREV_SCORPION(ah)))
    {
#if UMAC_SUPPORT_SMARTANTENNA
        ar9340_soc_gpio_cfg_output_mux(ah, gpio, ah_signal_type);
#endif
        return AH_TRUE;
    } else
    {
        /* Configure the MUX */
        ar9300_gpio_cfg_output_mux(ah, gpio, ah_signal_type);
    }

    /* 2 bits per output mode */
    gpio_shift = 2 * gpio;

    OS_REG_RMW(ah,
               AR_HOSTIF_REG(ah, AR_GPIO_OE_OUT),
               (AR_GPIO_OE_OUT_DRV_ALL << gpio_shift),
               (AR_GPIO_OE_OUT_DRV << gpio_shift));
    return AH_TRUE;
}