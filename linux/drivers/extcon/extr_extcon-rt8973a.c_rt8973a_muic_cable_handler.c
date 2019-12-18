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
struct rt8973a_muic_info {int /*<<< orphan*/  edev; int /*<<< orphan*/  dev; } ;
typedef  enum rt8973a_event_type { ____Placeholder_rt8973a_event_type } rt8973a_event_type ;

/* Variables and functions */
 unsigned int DM_DP_SWITCH_OPEN ; 
 unsigned int DM_DP_SWITCH_UART ; 
 unsigned int DM_DP_SWITCH_USB ; 
 int EINVAL ; 
 unsigned int EXTCON_CHG_USB_DCP ; 
 unsigned int EXTCON_CHG_USB_SDP ; 
 unsigned int EXTCON_JIG ; 
 unsigned int EXTCON_USB ; 
 unsigned int EXTCON_USB_HOST ; 
#define  RT8973A_EVENT_ATTACH 164 
#define  RT8973A_EVENT_DETACH 163 
#define  RT8973A_EVENT_OTP 162 
#define  RT8973A_EVENT_OVP 161 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S10_BUTTON 160 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S11_BUTTON 159 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S12_BUTTON 158 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S1_BUTTON 157 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S2_BUTTON 156 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S3_BUTTON 155 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S4_BUTTON 154 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S5_BUTTON 153 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S6_BUTTON 152 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S7_BUTTON 151 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S8_BUTTON 150 
#define  RT8973A_MUIC_ADC_AUDIO_REMOTE_S9_BUTTON 149 
#define  RT8973A_MUIC_ADC_AUDIO_SEND_END_BUTTON 148 
#define  RT8973A_MUIC_ADC_AUDIO_TYPE2 147 
#define  RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART 146 
#define  RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB 145 
#define  RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART 144 
#define  RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB 143 
#define  RT8973A_MUIC_ADC_OPEN 142 
#define  RT8973A_MUIC_ADC_OTG 141 
#define  RT8973A_MUIC_ADC_PHONE_POWERED_DEV 140 
#define  RT8973A_MUIC_ADC_RESERVED_ACC_1 139 
#define  RT8973A_MUIC_ADC_RESERVED_ACC_2 138 
#define  RT8973A_MUIC_ADC_RESERVED_ACC_3 137 
#define  RT8973A_MUIC_ADC_RESERVED_ACC_4 136 
#define  RT8973A_MUIC_ADC_RESERVED_ACC_5 135 
#define  RT8973A_MUIC_ADC_TA 134 
#define  RT8973A_MUIC_ADC_UNKNOWN_ACC_1 133 
#define  RT8973A_MUIC_ADC_UNKNOWN_ACC_2 132 
#define  RT8973A_MUIC_ADC_UNKNOWN_ACC_3 131 
#define  RT8973A_MUIC_ADC_UNKNOWN_ACC_4 130 
#define  RT8973A_MUIC_ADC_UNKNOWN_ACC_5 129 
#define  RT8973A_MUIC_ADC_USB 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,unsigned int,int) ; 
 int rt8973a_muic_get_cable_type (struct rt8973a_muic_info*) ; 
 int rt8973a_muic_set_path (struct rt8973a_muic_info*,unsigned int,int) ; 

__attribute__((used)) static int rt8973a_muic_cable_handler(struct rt8973a_muic_info *info,
					enum rt8973a_event_type event)
{
	static unsigned int prev_cable_type;
	unsigned int con_sw = DM_DP_SWITCH_UART;
	int ret, cable_type;
	unsigned int id;
	bool attached = false;

	switch (event) {
	case RT8973A_EVENT_ATTACH:
		cable_type = rt8973a_muic_get_cable_type(info);
		attached = true;
		break;
	case RT8973A_EVENT_DETACH:
		cable_type = prev_cable_type;
		attached = false;
		break;
	case RT8973A_EVENT_OVP:
	case RT8973A_EVENT_OTP:
		dev_warn(info->dev,
			"happen Over %s issue. Need to disconnect all cables\n",
			event == RT8973A_EVENT_OVP ? "Voltage" : "Temperature");
		cable_type = prev_cable_type;
		attached = false;
		break;
	default:
		dev_err(info->dev,
			"Cannot handle this event (event:%d)\n", event);
		return -EINVAL;
	}
	prev_cable_type = cable_type;

	switch (cable_type) {
	case RT8973A_MUIC_ADC_OTG:
		id = EXTCON_USB_HOST;
		con_sw = DM_DP_SWITCH_USB;
		break;
	case RT8973A_MUIC_ADC_TA:
		id = EXTCON_CHG_USB_DCP;
		con_sw = DM_DP_SWITCH_OPEN;
		break;
	case RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB:
	case RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB:
		id = EXTCON_JIG;
		con_sw = DM_DP_SWITCH_USB;
		break;
	case RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART:
	case RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART:
		id = EXTCON_JIG;
		con_sw = DM_DP_SWITCH_UART;
		break;
	case RT8973A_MUIC_ADC_USB:
		id = EXTCON_USB;
		con_sw = DM_DP_SWITCH_USB;
		break;
	case RT8973A_MUIC_ADC_OPEN:
		return 0;
	case RT8973A_MUIC_ADC_UNKNOWN_ACC_1:
	case RT8973A_MUIC_ADC_UNKNOWN_ACC_2:
	case RT8973A_MUIC_ADC_UNKNOWN_ACC_3:
	case RT8973A_MUIC_ADC_UNKNOWN_ACC_4:
	case RT8973A_MUIC_ADC_UNKNOWN_ACC_5:
		dev_warn(info->dev,
			"Unknown accessory type (adc:0x%x)\n", cable_type);
		return 0;
	case RT8973A_MUIC_ADC_AUDIO_SEND_END_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S1_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S2_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S3_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S4_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S5_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S6_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S7_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S8_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S9_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S10_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S11_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_REMOTE_S12_BUTTON:
	case RT8973A_MUIC_ADC_AUDIO_TYPE2:
		dev_warn(info->dev,
			"Audio device/button type (adc:0x%x)\n", cable_type);
		return 0;
	case RT8973A_MUIC_ADC_RESERVED_ACC_1:
	case RT8973A_MUIC_ADC_RESERVED_ACC_2:
	case RT8973A_MUIC_ADC_RESERVED_ACC_3:
	case RT8973A_MUIC_ADC_RESERVED_ACC_4:
	case RT8973A_MUIC_ADC_RESERVED_ACC_5:
	case RT8973A_MUIC_ADC_PHONE_POWERED_DEV:
		return 0;
	default:
		dev_err(info->dev,
			"Cannot handle this cable_type (adc:0x%x)\n",
			cable_type);
		return -EINVAL;
	}

	/* Change internal hardware path(DM_CON/DP_CON) */
	ret = rt8973a_muic_set_path(info, con_sw, attached);
	if (ret < 0)
		return ret;

	/* Change the state of external accessory */
	extcon_set_state_sync(info->edev, id, attached);
	if (id == EXTCON_USB)
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);

	return 0;
}