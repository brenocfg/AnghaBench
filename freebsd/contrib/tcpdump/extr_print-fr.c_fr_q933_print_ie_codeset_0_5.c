#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  FR_LMI_ANSI_LINK_VERIFY_IE 134 
#define  FR_LMI_ANSI_LINK_VERIFY_IE_91 133 
#define  FR_LMI_ANSI_PVC_STATUS_IE 132 
#define  FR_LMI_ANSI_REPORT_TYPE_IE 131 
#define  FR_LMI_CCITT_LINK_VERIFY_IE 130 
#define  FR_LMI_CCITT_PVC_STATUS_IE 129 
#define  FR_LMI_CCITT_REPORT_TYPE_IE 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  fr_lmi_report_type_ie_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 

__attribute__((used)) static int
fr_q933_print_ie_codeset_0_5(netdissect_options *ndo, u_int iecode,
                          u_int ielength, const u_char *p)
{
        u_int dlci;

        switch (iecode) {

        case FR_LMI_ANSI_REPORT_TYPE_IE: /* fall through */
        case FR_LMI_CCITT_REPORT_TYPE_IE:
            if (ielength < 1) {
                if (!ndo->ndo_vflag) {
                    ND_PRINT((ndo, ", "));
	        }
                ND_PRINT((ndo, "Invalid REPORT TYPE IE"));
                return 1;
            }
            if (ndo->ndo_vflag) {
                ND_PRINT((ndo, "%s (%u)",
                       tok2str(fr_lmi_report_type_ie_values,"unknown",p[0]),
                       p[0]));
	    }
            return 1;

        case FR_LMI_ANSI_LINK_VERIFY_IE: /* fall through */
        case FR_LMI_CCITT_LINK_VERIFY_IE:
        case FR_LMI_ANSI_LINK_VERIFY_IE_91:
            if (!ndo->ndo_vflag) {
                ND_PRINT((ndo, ", "));
	    }
            if (ielength < 2) {
                ND_PRINT((ndo, "Invalid LINK VERIFY IE"));
                return 1;
            }
            ND_PRINT((ndo, "TX Seq: %3d, RX Seq: %3d", p[0], p[1]));
            return 1;

        case FR_LMI_ANSI_PVC_STATUS_IE: /* fall through */
        case FR_LMI_CCITT_PVC_STATUS_IE:
            if (!ndo->ndo_vflag) {
                ND_PRINT((ndo, ", "));
	    }
            /* now parse the DLCI information element. */
            if ((ielength < 3) ||
                (p[0] & 0x80) ||
                ((ielength == 3) && !(p[1] & 0x80)) ||
                ((ielength == 4) && ((p[1] & 0x80) || !(p[2] & 0x80))) ||
                ((ielength == 5) && ((p[1] & 0x80) || (p[2] & 0x80) ||
                                   !(p[3] & 0x80))) ||
                (ielength > 5) ||
                !(p[ielength - 1] & 0x80)) {
                ND_PRINT((ndo, "Invalid DLCI in PVC STATUS IE"));
                return 1;
	    }

            dlci = ((p[0] & 0x3F) << 4) | ((p[1] & 0x78) >> 3);
            if (ielength == 4) {
                dlci = (dlci << 6) | ((p[2] & 0x7E) >> 1);
	    }
            else if (ielength == 5) {
                dlci = (dlci << 13) | (p[2] & 0x7F) | ((p[3] & 0x7E) >> 1);
	    }

            ND_PRINT((ndo, "DLCI %u: status %s%s", dlci,
                    p[ielength - 1] & 0x8 ? "New, " : "",
                    p[ielength - 1] & 0x2 ? "Active" : "Inactive"));
            return 1;
	}

        return 0;
}