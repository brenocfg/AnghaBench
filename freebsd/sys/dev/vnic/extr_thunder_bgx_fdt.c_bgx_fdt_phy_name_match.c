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
struct bgx {int qlm_mode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  QLM_MODE_10G_KR_4X1 134 
#define  QLM_MODE_40G_KR4_1X4 133 
#define  QLM_MODE_RXAUI_2X2 132 
#define  QLM_MODE_SGMII 131 
#define  QLM_MODE_XAUI_1X4 130 
#define  QLM_MODE_XFI_4X1 129 
#define  QLM_MODE_XLAUI_1X4 128 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static boolean_t
bgx_fdt_phy_name_match(struct bgx *bgx, char *phy_name, ssize_t size)
{
	const char *type;
	ssize_t sz;

	switch (bgx->qlm_mode) {
	case QLM_MODE_SGMII:
		type = "sgmii";
		sz = sizeof("sgmii");
		break;
	case QLM_MODE_XAUI_1X4:
		type = "xaui";
		sz = sizeof("xaui");
		if (sz < size)
			return (FALSE);
		if (strncmp(phy_name, type, sz) == 0)
			return (TRUE);
		type = "dxaui";
		sz = sizeof("dxaui");
		break;
	case QLM_MODE_RXAUI_2X2:
		type = "raui";
		sz = sizeof("raui");
		break;
	case QLM_MODE_XFI_4X1:
		type = "xfi";
		sz = sizeof("xfi");
		break;
	case QLM_MODE_XLAUI_1X4:
		type = "xlaui";
		sz = sizeof("xlaui");
		break;
	case QLM_MODE_10G_KR_4X1:
		type = "xfi-10g-kr";
		sz = sizeof("xfi-10g-kr");
		break;
	case QLM_MODE_40G_KR4_1X4:
		type = "xlaui-40g-kr";
		sz = sizeof("xlaui-40g-kr");
		break;
	default:
		return (FALSE);
	}

	if (sz > size)
		return (FALSE);
	if (strncmp(phy_name, type, sz - 1) == 0 &&
	    (phy_name[sz - 1] == '\0' || phy_name[sz - 1] == '@'))
		return (TRUE);

	return (FALSE);
}