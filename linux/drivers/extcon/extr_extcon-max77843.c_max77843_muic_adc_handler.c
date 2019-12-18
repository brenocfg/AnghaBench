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
struct max77843_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  prev_cable_type; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX77843_CABLE_GROUP_ADC ; 
#define  MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE1 159 
#define  MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE2 158 
#define  MAX77843_MUIC_ADC_AV_CABLE_NOLOAD 157 
#define  MAX77843_MUIC_ADC_CEA936A_TYPE1_CHG 156 
#define  MAX77843_MUIC_ADC_CEA936A_TYPE2_CHG 155 
#define  MAX77843_MUIC_ADC_FACTORY_MODE_UART_OFF 154 
#define  MAX77843_MUIC_ADC_FACTORY_MODE_UART_ON 153 
#define  MAX77843_MUIC_ADC_FACTORY_MODE_USB_OFF 152 
#define  MAX77843_MUIC_ADC_FACTORY_MODE_USB_ON 151 
#define  MAX77843_MUIC_ADC_GROUND 150 
#define  MAX77843_MUIC_ADC_OPEN 149 
#define  MAX77843_MUIC_ADC_PHONE_POWERED_DEV 148 
#define  MAX77843_MUIC_ADC_REMOTE_S10_BUTTON 147 
#define  MAX77843_MUIC_ADC_REMOTE_S11_BUTTON 146 
#define  MAX77843_MUIC_ADC_REMOTE_S12_BUTTON 145 
#define  MAX77843_MUIC_ADC_REMOTE_S1_BUTTON 144 
#define  MAX77843_MUIC_ADC_REMOTE_S2_BUTTON 143 
#define  MAX77843_MUIC_ADC_REMOTE_S3_BUTTON 142 
#define  MAX77843_MUIC_ADC_REMOTE_S4_BUTTON 141 
#define  MAX77843_MUIC_ADC_REMOTE_S5_BUTTON 140 
#define  MAX77843_MUIC_ADC_REMOTE_S6_BUTTON 139 
#define  MAX77843_MUIC_ADC_REMOTE_S7_BUTTON 138 
#define  MAX77843_MUIC_ADC_REMOTE_S8_BUTTON 137 
#define  MAX77843_MUIC_ADC_REMOTE_S9_BUTTON 136 
#define  MAX77843_MUIC_ADC_RESERVED_ACC_1 135 
#define  MAX77843_MUIC_ADC_RESERVED_ACC_2 134 
#define  MAX77843_MUIC_ADC_RESERVED_ACC_3 133 
#define  MAX77843_MUIC_ADC_RESERVED_ACC_4 132 
#define  MAX77843_MUIC_ADC_RESERVED_ACC_5 131 
#define  MAX77843_MUIC_ADC_SEND_END_BUTTON 130 
#define  MAX77843_MUIC_ADC_TTY_CONVERTER 129 
#define  MAX77843_MUIC_ADC_UART_CABLE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int max77843_muic_adc_gnd_handler (struct max77843_muic_info*) ; 
 int max77843_muic_dock_handler (struct max77843_muic_info*,int) ; 
 int max77843_muic_get_cable_type (struct max77843_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int max77843_muic_jig_handler (struct max77843_muic_info*,int,int) ; 

__attribute__((used)) static int max77843_muic_adc_handler(struct max77843_muic_info *info)
{
	int ret, cable_type;
	bool attached;

	cable_type = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_ADC, &attached);

	dev_dbg(info->dev,
		"external connector is %s (adc:0x%02x, prev_adc:0x%x)\n",
		attached ? "attached" : "detached", cable_type,
		info->prev_cable_type);

	switch (cable_type) {
	case MAX77843_MUIC_ADC_RESERVED_ACC_3: /* SmartDock */
		ret = max77843_muic_dock_handler(info, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX77843_MUIC_ADC_GROUND:
		ret = max77843_muic_adc_gnd_handler(info);
		if (ret < 0)
			return ret;
		break;
	case MAX77843_MUIC_ADC_FACTORY_MODE_USB_OFF:
	case MAX77843_MUIC_ADC_FACTORY_MODE_USB_ON:
	case MAX77843_MUIC_ADC_FACTORY_MODE_UART_OFF:
		ret = max77843_muic_jig_handler(info, cable_type, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX77843_MUIC_ADC_SEND_END_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S1_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S2_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S3_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S4_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S5_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S6_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S7_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S8_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S9_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S10_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S11_BUTTON:
	case MAX77843_MUIC_ADC_REMOTE_S12_BUTTON:
	case MAX77843_MUIC_ADC_RESERVED_ACC_1:
	case MAX77843_MUIC_ADC_RESERVED_ACC_2:
	case MAX77843_MUIC_ADC_RESERVED_ACC_4:
	case MAX77843_MUIC_ADC_RESERVED_ACC_5:
	case MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE2:
	case MAX77843_MUIC_ADC_PHONE_POWERED_DEV:
	case MAX77843_MUIC_ADC_TTY_CONVERTER:
	case MAX77843_MUIC_ADC_UART_CABLE:
	case MAX77843_MUIC_ADC_CEA936A_TYPE1_CHG:
	case MAX77843_MUIC_ADC_AV_CABLE_NOLOAD:
	case MAX77843_MUIC_ADC_CEA936A_TYPE2_CHG:
	case MAX77843_MUIC_ADC_FACTORY_MODE_UART_ON:
	case MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE1:
	case MAX77843_MUIC_ADC_OPEN:
		dev_err(info->dev,
			"accessory is %s but it isn't used (adc:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		return -EAGAIN;
	default:
		dev_err(info->dev,
			"failed to detect %s accessory (adc:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		return -EINVAL;
	}

	return 0;
}