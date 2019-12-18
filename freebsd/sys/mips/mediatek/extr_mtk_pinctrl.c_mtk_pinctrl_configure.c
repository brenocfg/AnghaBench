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
typedef  int uint32_t ;
struct mtk_pin_group {int dummy; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  MTK_SOC_MT7620A 140 
#define  MTK_SOC_MT7620N 139 
#define  MTK_SOC_MT7621 138 
#define  MTK_SOC_MT7628 137 
#define  MTK_SOC_MT7688 136 
#define  MTK_SOC_RT2880 135 
#define  MTK_SOC_RT3050 134 
#define  MTK_SOC_RT3052 133 
#define  MTK_SOC_RT3350 132 
#define  MTK_SOC_RT3352 131 
#define  MTK_SOC_RT3662 130 
#define  MTK_SOC_RT3883 129 
#define  MTK_SOC_RT5350 128 
 int OF_child (int) ; 
 int OF_node_from_xref (int) ; 
 int OF_peer (int) ; 
 struct mtk_pin_group* mt7620_pintable ; 
 struct mtk_pin_group* mt7621_pintable ; 
 struct mtk_pin_group* mt7628_pintable ; 
 int mtk_pinctrl_process_node (int /*<<< orphan*/ ,struct mtk_pin_group*,int) ; 
 int mtk_soc_get_socid () ; 
 struct mtk_pin_group* rt2880_pintable ; 
 struct mtk_pin_group* rt3050_pintable ; 
 struct mtk_pin_group* rt3352_pintable ; 
 struct mtk_pin_group* rt3883_pintable ; 
 struct mtk_pin_group* rt5350_pintable ; 

__attribute__((used)) static int
mtk_pinctrl_configure(device_t dev, phandle_t cfgxref)
{
	struct mtk_pin_group *pintable;
	phandle_t node, child;
	uint32_t socid;
	int ret;

	node = OF_node_from_xref(cfgxref);
	ret = 0;

	/* Now, get the system type, so we can get the proper GPIO mode array */
	socid = mtk_soc_get_socid();

	switch (socid) {
	case MTK_SOC_RT2880:
		pintable = rt2880_pintable;
		break;
	case MTK_SOC_RT3050: /* fallthrough */
	case MTK_SOC_RT3052:
	case MTK_SOC_RT3350:
		pintable = rt3050_pintable;
		break;
	case MTK_SOC_RT3352:
		pintable = rt3352_pintable;
		break;
	case MTK_SOC_RT3662: /* fallthrough */
	case MTK_SOC_RT3883:
		pintable = rt3883_pintable;
		break;
	case MTK_SOC_RT5350:
		pintable = rt5350_pintable;
		break;
	case MTK_SOC_MT7620A: /* fallthrough */
	case MTK_SOC_MT7620N:
		pintable = mt7620_pintable;
		break;
	case MTK_SOC_MT7628: /* fallthrough */
	case MTK_SOC_MT7688:
		pintable = mt7628_pintable;
		break;
	case MTK_SOC_MT7621:
		pintable = mt7621_pintable;
		break;
	default:
		ret = ENOENT;
		goto out;
	}

	/*
	 * OpenWRT dts files have single child within the pinctrl nodes, which
	 * contains the 'ralink,group' and 'ralink,function' properties.
	 */ 
	for (child = OF_child(node); child != 0 && child != -1;
	    child = OF_peer(child)) {
		if ((ret = mtk_pinctrl_process_node(dev, pintable, child)) != 0)
			return (ret);
	}

out:
	return (ret);
}