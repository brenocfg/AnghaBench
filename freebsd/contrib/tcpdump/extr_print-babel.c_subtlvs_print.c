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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int const MESSAGE_HELLO ; 
 int const MESSAGE_IHU ; 
#define  MESSAGE_SUB_DIVERSITY 130 
 int MESSAGE_SUB_PAD1 ; 
#define  MESSAGE_SUB_PADN 129 
#define  MESSAGE_SUB_TIMESTAMP 128 
 int const MESSAGE_UPDATE ; 
 int const MESSAGE_UPDATE_SRC_SPECIFIC ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diversity_str ; 
 int /*<<< orphan*/  format_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
subtlvs_print(netdissect_options *ndo,
              const u_char *cp, const u_char *ep, const uint8_t tlv_type)
{
    uint8_t subtype, sublen;
    const char *sep;
    uint32_t t1, t2;

    while (cp < ep) {
        subtype = *cp++;
        if(subtype == MESSAGE_SUB_PAD1) {
            ND_PRINT((ndo, " sub-pad1"));
            continue;
        }
        if(cp == ep)
            goto invalid;
        sublen = *cp++;
        if(cp + sublen > ep)
            goto invalid;

        switch(subtype) {
        case MESSAGE_SUB_PADN:
            ND_PRINT((ndo, " sub-padn"));
            cp += sublen;
            break;
        case MESSAGE_SUB_DIVERSITY:
            ND_PRINT((ndo, " sub-diversity"));
            if (sublen == 0) {
                ND_PRINT((ndo, " empty"));
                break;
            }
            sep = " ";
            while(sublen--) {
                ND_PRINT((ndo, "%s%s", sep, tok2str(diversity_str, "%u", *cp++)));
                sep = "-";
            }
            if(tlv_type != MESSAGE_UPDATE &&
               tlv_type != MESSAGE_UPDATE_SRC_SPECIFIC)
                ND_PRINT((ndo, " (bogus)"));
            break;
        case MESSAGE_SUB_TIMESTAMP:
            ND_PRINT((ndo, " sub-timestamp"));
            if(tlv_type == MESSAGE_HELLO) {
                if(sublen < 4)
                    goto invalid;
                t1 = EXTRACT_32BITS(cp);
                ND_PRINT((ndo, " %s", format_timestamp(t1)));
            } else if(tlv_type == MESSAGE_IHU) {
                if(sublen < 8)
                    goto invalid;
                t1 = EXTRACT_32BITS(cp);
                ND_PRINT((ndo, " %s", format_timestamp(t1)));
                t2 = EXTRACT_32BITS(cp + 4);
                ND_PRINT((ndo, "|%s", format_timestamp(t2)));
            } else
                ND_PRINT((ndo, " (bogus)"));
            cp += sublen;
            break;
        default:
            ND_PRINT((ndo, " sub-unknown-0x%02x", subtype));
            cp += sublen;
        } /* switch */
    } /* while */
    return;

 invalid:
    ND_PRINT((ndo, "%s", istr));
}