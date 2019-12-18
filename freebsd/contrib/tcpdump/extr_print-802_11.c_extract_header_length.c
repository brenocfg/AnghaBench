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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  CTRL_ACK 139 
 int CTRL_ACK_HDRLEN ; 
#define  CTRL_BA 138 
#define  CTRL_BAR 137 
 int CTRL_BAR_HDRLEN ; 
 int CTRL_BA_HDRLEN ; 
#define  CTRL_CF_END 136 
#define  CTRL_CONTROL_WRAPPER 135 
 int CTRL_CONTROL_WRAPPER_HDRLEN ; 
#define  CTRL_CTS 134 
 int CTRL_CTS_HDRLEN ; 
#define  CTRL_END_ACK 133 
 int CTRL_END_ACK_HDRLEN ; 
 int CTRL_END_HDRLEN ; 
#define  CTRL_PS_POLL 132 
 int CTRL_PS_POLL_HDRLEN ; 
#define  CTRL_RTS 131 
 int CTRL_RTS_HDRLEN ; 
 int /*<<< orphan*/  DATA_FRAME_IS_QOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_FROM_DS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_TO_DS (int /*<<< orphan*/ ) ; 
 int FC_TYPE (int /*<<< orphan*/ ) ; 
 int MGMT_HDRLEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
#define  T_CTRL 130 
#define  T_DATA 129 
#define  T_MGMT 128 

__attribute__((used)) static int
extract_header_length(netdissect_options *ndo,
                      uint16_t fc)
{
	int len;

	switch (FC_TYPE(fc)) {
	case T_MGMT:
		return MGMT_HDRLEN;
	case T_CTRL:
		switch (FC_SUBTYPE(fc)) {
		case CTRL_CONTROL_WRAPPER:
			return CTRL_CONTROL_WRAPPER_HDRLEN;
		case CTRL_BAR:
			return CTRL_BAR_HDRLEN;
		case CTRL_BA:
			return CTRL_BA_HDRLEN;
		case CTRL_PS_POLL:
			return CTRL_PS_POLL_HDRLEN;
		case CTRL_RTS:
			return CTRL_RTS_HDRLEN;
		case CTRL_CTS:
			return CTRL_CTS_HDRLEN;
		case CTRL_ACK:
			return CTRL_ACK_HDRLEN;
		case CTRL_CF_END:
			return CTRL_END_HDRLEN;
		case CTRL_END_ACK:
			return CTRL_END_ACK_HDRLEN;
		default:
			ND_PRINT((ndo, "unknown 802.11 ctrl frame subtype (%d)", FC_SUBTYPE(fc)));
			return 0;
		}
	case T_DATA:
		len = (FC_TO_DS(fc) && FC_FROM_DS(fc)) ? 30 : 24;
		if (DATA_FRAME_IS_QOS(FC_SUBTYPE(fc)))
			len += 2;
		return len;
	default:
		ND_PRINT((ndo, "unknown 802.11 frame type (%d)", FC_TYPE(fc)));
		return 0;
	}
}