#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
#define  UDLD_DEVICE_ID_TLV 134 
#define  UDLD_DEVICE_NAME_TLV 133 
#define  UDLD_ECHO_TLV 132 
 int UDLD_EXTRACT_OPCODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  UDLD_EXTRACT_VERSION (int /*<<< orphan*/  const) ; 
 int UDLD_HEADER_LEN ; 
#define  UDLD_MESSAGE_INTERVAL_TLV 131 
#define  UDLD_PORT_ID_TLV 130 
#define  UDLD_SEQ_NUMBER_TLV 129 
#define  UDLD_TIMEOUT_INTERVAL_TLV 128 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fn_printn (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fn_printzp (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 
 int /*<<< orphan*/  udld_code_values ; 
 int /*<<< orphan*/  udld_flags_values ; 
 int /*<<< orphan*/  udld_tlv_values ; 

void
udld_print (netdissect_options *ndo, const u_char *pptr, u_int length)
{
    int code, type, len;
    const u_char *tptr;

    if (length < UDLD_HEADER_LEN)
        goto trunc;

    tptr = pptr;

    ND_TCHECK2(*tptr, UDLD_HEADER_LEN);

    code = UDLD_EXTRACT_OPCODE(*tptr);

    ND_PRINT((ndo, "UDLDv%u, Code %s (%x), Flags [%s] (0x%02x), length %u",
           UDLD_EXTRACT_VERSION(*tptr),
           tok2str(udld_code_values, "Reserved", code),
           code,
           bittok2str(udld_flags_values, "none", *(tptr+1)),
           *(tptr+1),
           length));

    /*
     * In non-verbose mode, just print version and opcode type
     */
    if (ndo->ndo_vflag < 1) {
	return;
    }

    ND_PRINT((ndo, "\n\tChecksum 0x%04x (unverified)", EXTRACT_16BITS(tptr+2)));

    tptr += UDLD_HEADER_LEN;

    while (tptr < (pptr+length)) {

        ND_TCHECK2(*tptr, 4);
	type = EXTRACT_16BITS(tptr);
        len  = EXTRACT_16BITS(tptr+2);

        ND_PRINT((ndo, "\n\t%s (0x%04x) TLV, length %u",
               tok2str(udld_tlv_values, "Unknown", type),
               type, len));

        if (type == 0)
            goto invalid;

        /* infinite loop check */
        if (len <= 4)
            goto invalid;

        len -= 4;
        tptr += 4;

        ND_TCHECK2(*tptr, len);

        switch (type) {
        case UDLD_DEVICE_ID_TLV:
        case UDLD_PORT_ID_TLV:
        case UDLD_DEVICE_NAME_TLV:
            ND_PRINT((ndo, ", "));
            fn_printzp(ndo, tptr, len, NULL);
            break;

        case UDLD_ECHO_TLV:
            ND_PRINT((ndo, ", "));
            (void)fn_printn(ndo, tptr, len, NULL);
            break;

        case UDLD_MESSAGE_INTERVAL_TLV:
        case UDLD_TIMEOUT_INTERVAL_TLV:
            if (len != 1)
                goto invalid;
            ND_PRINT((ndo, ", %us", (*tptr)));
            break;

        case UDLD_SEQ_NUMBER_TLV:
            if (len != 4)
                goto invalid;
            ND_PRINT((ndo, ", %u", EXTRACT_32BITS(tptr)));
            break;

        default:
            break;
        }
        tptr += len;
    }

    return;

invalid:
    ND_PRINT((ndo, "%s", istr));
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}