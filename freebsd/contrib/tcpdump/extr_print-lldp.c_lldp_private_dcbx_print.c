#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  tlv ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int EXTRACT_24BITS (int const*) ; 
 int EXTRACT_32BITS (int const*) ; 
 int FALSE ; 
#define  LLDP_DCBX_APPLICATION_TLV 131 
#define  LLDP_DCBX_CONTROL_TLV 130 
#define  LLDP_DCBX_PRIORITY_FLOW_CONTROL_TLV 129 
#define  LLDP_DCBX_PRIORITY_GROUPS_TLV 128 
 int LLDP_DCBX_SUBTYPE_1 ; 
 int LLDP_EXTRACT_LEN (int /*<<< orphan*/ ) ; 
 int LLDP_EXTRACT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  lldp_dcbx_subtype_values ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int const*,char*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
lldp_private_dcbx_print(netdissect_options *ndo,
                        const u_char *pptr, u_int len)
{
    int subtype, hexdump = FALSE;
    uint8_t tval;
    uint16_t tlv;
    uint32_t i, pgval, uval;
    u_int tlen, tlv_type, tlv_len;
    const u_char *tptr, *mptr;

    if (len < 4) {
        return hexdump;
    }
    subtype = *(pptr+3);

    ND_PRINT((ndo, "\n\t  %s Subtype (%u)",
           tok2str(lldp_dcbx_subtype_values, "unknown", subtype),
           subtype));

    /* by passing old version */
    if (subtype == LLDP_DCBX_SUBTYPE_1)
	return TRUE;

    tptr = pptr + 4;
    tlen = len - 4;

    while (tlen >= sizeof(tlv)) {

        ND_TCHECK2(*tptr, sizeof(tlv));

        tlv = EXTRACT_16BITS(tptr);

        tlv_type = LLDP_EXTRACT_TYPE(tlv);
        tlv_len = LLDP_EXTRACT_LEN(tlv);
        hexdump = FALSE;

        tlen -= sizeof(tlv);
        tptr += sizeof(tlv);

        /* loop check */
        if (!tlv_type || !tlv_len) {
            break;
        }

        ND_TCHECK2(*tptr, tlv_len);
        if (tlen < tlv_len) {
            goto trunc;
        }

	/* decode every tlv */
        switch (tlv_type) {
        case LLDP_DCBX_CONTROL_TLV:
            if (tlv_len < 10) {
                goto trunc;
            }
	    ND_PRINT((ndo, "\n\t    Control - Protocol Control (type 0x%x, length %d)",
		LLDP_DCBX_CONTROL_TLV, tlv_len));
	    ND_PRINT((ndo, "\n\t      Oper_Version: %d", *tptr));
	    ND_PRINT((ndo, "\n\t      Max_Version: %d", *(tptr + 1)));
	    ND_PRINT((ndo, "\n\t      Sequence Number: %d", EXTRACT_32BITS(tptr + 2)));
	    ND_PRINT((ndo, "\n\t      Acknowledgement Number: %d",
					EXTRACT_32BITS(tptr + 6)));
	    break;
        case LLDP_DCBX_PRIORITY_GROUPS_TLV:
            if (tlv_len < 17) {
                goto trunc;
            }
	    ND_PRINT((ndo, "\n\t    Feature - Priority Group (type 0x%x, length %d)",
		LLDP_DCBX_PRIORITY_GROUPS_TLV, tlv_len));
	    ND_PRINT((ndo, "\n\t      Oper_Version: %d", *tptr));
	    ND_PRINT((ndo, "\n\t      Max_Version: %d", *(tptr + 1)));
	    ND_PRINT((ndo, "\n\t      Info block(0x%02X): ", *(tptr + 2)));
	    tval = *(tptr+2);
	    ND_PRINT((ndo, "Enable bit: %d, Willing bit: %d, Error Bit: %d",
		(tval &  0x80) ? 1 : 0, (tval &  0x40) ? 1 : 0,
		(tval &  0x20) ? 1 : 0));
	    ND_PRINT((ndo, "\n\t      SubType: %d", *(tptr + 3)));
	    ND_PRINT((ndo, "\n\t      Priority Allocation"));

	    /*
	     * Array of 8 4-bit priority group ID values; we fetch all
	     * 32 bits and extract each nibble.
	     */
	    pgval = EXTRACT_32BITS(tptr+4);
	    for (i = 0; i <= 7; i++) {
		ND_PRINT((ndo, "\n\t          PgId_%d: %d",
			i, (pgval >> (28 - 4 * i)) & 0xF));
	    }
	    ND_PRINT((ndo, "\n\t      Priority Group Allocation"));
	    for (i = 0; i <= 7; i++)
		ND_PRINT((ndo, "\n\t          Pg percentage[%d]: %d", i, *(tptr + 8 + i)));
	    ND_PRINT((ndo, "\n\t      NumTCsSupported: %d", *(tptr + 8 + 8)));
	    break;
        case LLDP_DCBX_PRIORITY_FLOW_CONTROL_TLV:
            if (tlv_len < 6) {
                goto trunc;
            }
	    ND_PRINT((ndo, "\n\t    Feature - Priority Flow Control"));
	    ND_PRINT((ndo, " (type 0x%x, length %d)",
		LLDP_DCBX_PRIORITY_FLOW_CONTROL_TLV, tlv_len));
	    ND_PRINT((ndo, "\n\t      Oper_Version: %d", *tptr));
	    ND_PRINT((ndo, "\n\t      Max_Version: %d", *(tptr + 1)));
	    ND_PRINT((ndo, "\n\t      Info block(0x%02X): ", *(tptr + 2)));
	    tval = *(tptr+2);
	    ND_PRINT((ndo, "Enable bit: %d, Willing bit: %d, Error Bit: %d",
		(tval &  0x80) ? 1 : 0, (tval &  0x40) ? 1 : 0,
		(tval &  0x20) ? 1 : 0));
	    ND_PRINT((ndo, "\n\t      SubType: %d", *(tptr + 3)));
	    tval = *(tptr+4);
	    ND_PRINT((ndo, "\n\t      PFC Config (0x%02X)", *(tptr + 4)));
	    for (i = 0; i <= 7; i++)
		ND_PRINT((ndo, "\n\t          Priority Bit %d: %s",
		    i, (tval & (1 << i)) ? "Enabled" : "Disabled"));
	    ND_PRINT((ndo, "\n\t      NumTCPFCSupported: %d", *(tptr + 5)));
	    break;
        case LLDP_DCBX_APPLICATION_TLV:
            if (tlv_len < 4) {
                goto trunc;
            }
	    ND_PRINT((ndo, "\n\t    Feature - Application (type 0x%x, length %d)",
		LLDP_DCBX_APPLICATION_TLV, tlv_len));
	    ND_PRINT((ndo, "\n\t      Oper_Version: %d", *tptr));
	    ND_PRINT((ndo, "\n\t      Max_Version: %d", *(tptr + 1)));
	    ND_PRINT((ndo, "\n\t      Info block(0x%02X): ", *(tptr + 2)));
	    tval = *(tptr+2);
	    ND_PRINT((ndo, "Enable bit: %d, Willing bit: %d, Error Bit: %d",
		(tval &  0x80) ? 1 : 0, (tval &  0x40) ? 1 : 0,
		(tval &  0x20) ? 1 : 0));
	    ND_PRINT((ndo, "\n\t      SubType: %d", *(tptr + 3)));
	    tval = tlv_len - 4;
	    mptr = tptr + 4;
	    while (tval >= 6) {
		ND_PRINT((ndo, "\n\t      Application Value"));
		ND_PRINT((ndo, "\n\t          Application Protocol ID: 0x%04x",
			EXTRACT_16BITS(mptr)));
		uval = EXTRACT_24BITS(mptr+2);
		ND_PRINT((ndo, "\n\t          SF (0x%x) Application Protocol ID is %s",
			(uval >> 22),
			(uval >> 22) ? "Socket Number" : "L2 EtherType"));
		ND_PRINT((ndo, "\n\t          OUI: 0x%06x", uval & 0x3fffff));
		ND_PRINT((ndo, "\n\t          User Priority Map: 0x%02x", *(mptr + 5)));
		tval = tval - 6;
		mptr = mptr + 6;
	    }
	    break;
	default:
	    hexdump = TRUE;
	    break;
	}

        /* do we also want to see a hex dump ? */
        if (ndo->ndo_vflag > 1 || (ndo->ndo_vflag && hexdump)) {
	    print_unknown_data(ndo, tptr, "\n\t    ", tlv_len);
        }

        tlen -= tlv_len;
        tptr += tlv_len;
    }

 trunc:
    return hexdump;
}