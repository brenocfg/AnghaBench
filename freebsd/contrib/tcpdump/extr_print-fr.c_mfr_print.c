#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int u_char ;
struct timeval {int dummy; } ;
struct ie_tlv_header_t {int dummy; } ;
struct TYPE_8__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int const MFR_BEC_MASK ; 
 int const MFR_B_BIT ; 
 int const MFR_CTRL_FRAME ; 
#define  MFR_CTRL_IE_BUNDLE_ID 133 
#define  MFR_CTRL_IE_CAUSE 132 
#define  MFR_CTRL_IE_LINK_ID 131 
#define  MFR_CTRL_IE_MAGIC_NUM 130 
#define  MFR_CTRL_IE_TIMESTAMP 129 
#define  MFR_CTRL_IE_VENDOR_EXT 128 
 int const MFR_FRAG_FRAME ; 
 int MFR_ID_STRING_MAXLEN ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  fr_print (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  frf_flag_values ; 
 int /*<<< orphan*/  mfr_ctrl_ie_values ; 
 int /*<<< orphan*/  mfr_ctrl_msg_values ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int const*,char*,int) ; 
 int /*<<< orphan*/  safeputchar (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  ts_print (TYPE_1__*,struct timeval const*) ; 

u_int
mfr_print(netdissect_options *ndo,
          register const u_char *p, u_int length)
{
    u_int tlen,idx,hdr_len = 0;
    uint16_t sequence_num;
    uint8_t ie_type,ie_len;
    const uint8_t *tptr;


/*
 * FRF.16 Link Integrity Control Frame
 *
 *      7    6    5    4    3    2    1    0
 *    +----+----+----+----+----+----+----+----+
 *    | B  | E  | C=1| 0    0    0    0  | EA |
 *    +----+----+----+----+----+----+----+----+
 *    | 0    0    0    0    0    0    0    0  |
 *    +----+----+----+----+----+----+----+----+
 *    |              message type             |
 *    +----+----+----+----+----+----+----+----+
 */

    ND_TCHECK2(*p, 4); /* minimum frame header length */

    if ((p[0] & MFR_BEC_MASK) == MFR_CTRL_FRAME && p[1] == 0) {
        ND_PRINT((ndo, "FRF.16 Control, Flags [%s], %s, length %u",
               bittok2str(frf_flag_values,"none",(p[0] & MFR_BEC_MASK)),
               tok2str(mfr_ctrl_msg_values,"Unknown Message (0x%02x)",p[2]),
               length));
        tptr = p + 3;
        tlen = length -3;
        hdr_len = 3;

        if (!ndo->ndo_vflag)
            return hdr_len;

        while (tlen>sizeof(struct ie_tlv_header_t)) {
            ND_TCHECK2(*tptr, sizeof(struct ie_tlv_header_t));
            ie_type=tptr[0];
            ie_len=tptr[1];

            ND_PRINT((ndo, "\n\tIE %s (%u), length %u: ",
                   tok2str(mfr_ctrl_ie_values,"Unknown",ie_type),
                   ie_type,
                   ie_len));

            /* infinite loop check */
            if (ie_type == 0 || ie_len <= sizeof(struct ie_tlv_header_t))
                return hdr_len;

            ND_TCHECK2(*tptr, ie_len);
            tptr+=sizeof(struct ie_tlv_header_t);
            /* tlv len includes header */
            ie_len-=sizeof(struct ie_tlv_header_t);
            tlen-=sizeof(struct ie_tlv_header_t);

            switch (ie_type) {

            case MFR_CTRL_IE_MAGIC_NUM:
                ND_PRINT((ndo, "0x%08x", EXTRACT_32BITS(tptr)));
                break;

            case MFR_CTRL_IE_BUNDLE_ID: /* same message format */
            case MFR_CTRL_IE_LINK_ID:
                for (idx = 0; idx < ie_len && idx < MFR_ID_STRING_MAXLEN; idx++) {
                    if (*(tptr+idx) != 0) /* don't print null termination */
                        safeputchar(ndo, *(tptr + idx));
                    else
                        break;
                }
                break;

            case MFR_CTRL_IE_TIMESTAMP:
                if (ie_len == sizeof(struct timeval)) {
                    ts_print(ndo, (const struct timeval *)tptr);
                    break;
                }
                /* fall through and hexdump if no unix timestamp */

                /*
                 * FIXME those are the defined IEs that lack a decoder
                 * you are welcome to contribute code ;-)
                 */

            case MFR_CTRL_IE_VENDOR_EXT:
            case MFR_CTRL_IE_CAUSE:

            default:
                if (ndo->ndo_vflag <= 1)
                    print_unknown_data(ndo, tptr, "\n\t  ", ie_len);
                break;
            }

            /* do we want to see a hexdump of the IE ? */
            if (ndo->ndo_vflag > 1 )
                print_unknown_data(ndo, tptr, "\n\t  ", ie_len);

            tlen-=ie_len;
            tptr+=ie_len;
        }
        return hdr_len;
    }
/*
 * FRF.16 Fragmentation Frame
 *
 *      7    6    5    4    3    2    1    0
 *    +----+----+----+----+----+----+----+----+
 *    | B  | E  | C=0|seq. (high 4 bits) | EA  |
 *    +----+----+----+----+----+----+----+----+
 *    |        sequence  (low 8 bits)         |
 *    +----+----+----+----+----+----+----+----+
 *    |        DLCI (6 bits)        | CR | EA  |
 *    +----+----+----+----+----+----+----+----+
 *    |   DLCI (4 bits)   |FECN|BECN| DE | EA |
 *    +----+----+----+----+----+----+----+----+
 */

    sequence_num = (p[0]&0x1e)<<7 | p[1];
    /* whole packet or first fragment ? */
    if ((p[0] & MFR_BEC_MASK) == MFR_FRAG_FRAME ||
        (p[0] & MFR_BEC_MASK) == MFR_B_BIT) {
        ND_PRINT((ndo, "FRF.16 Frag, seq %u, Flags [%s], ",
               sequence_num,
               bittok2str(frf_flag_values,"none",(p[0] & MFR_BEC_MASK))));
        hdr_len = 2;
        fr_print(ndo, p+hdr_len,length-hdr_len);
        return hdr_len;
    }

    /* must be a middle or the last fragment */
    ND_PRINT((ndo, "FRF.16 Frag, seq %u, Flags [%s]",
           sequence_num,
           bittok2str(frf_flag_values,"none",(p[0] & MFR_BEC_MASK))));
    print_unknown_data(ndo, p, "\n\t", length);

    return hdr_len;

 trunc:
    ND_PRINT((ndo, "[|mfr]"));
    return length;
}