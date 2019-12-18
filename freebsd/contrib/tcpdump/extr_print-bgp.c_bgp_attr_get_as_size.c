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
typedef  scalar_t__ uint8_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ BGPTYPE_AS4_PATH ; 
 int const BGP_AS_SEG_TYPE_MAX ; 
 int const BGP_AS_SEG_TYPE_MIN ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 

__attribute__((used)) static int
bgp_attr_get_as_size(netdissect_options *ndo,
                     uint8_t bgpa_type, const u_char *pptr, int len)
{
    const u_char *tptr = pptr;

    /*
     * If the path attribute is the optional AS4 path type, then we already
     * know, that ASs must be encoded in 4 byte format.
     */
    if (bgpa_type == BGPTYPE_AS4_PATH) {
        return 4;
    }

    /*
     * Let us assume that ASs are of 2 bytes in size, and check if the AS-Path
     * TLV is good. If not, ask the caller to try with AS encoded as 4 bytes
     * each.
     */
    while (tptr < pptr + len) {
        ND_TCHECK(tptr[0]);

        /*
         * If we do not find a valid segment type, our guess might be wrong.
         */
        if (tptr[0] < BGP_AS_SEG_TYPE_MIN || tptr[0] > BGP_AS_SEG_TYPE_MAX) {
            goto trunc;
        }
        ND_TCHECK(tptr[1]);
        tptr += 2 + tptr[1] * 2;
    }

    /*
     * If we correctly reached end of the AS path attribute data content,
     * then most likely ASs were indeed encoded as 2 bytes.
     */
    if (tptr == pptr + len) {
        return 2;
    }

trunc:

    /*
     * We can come here, either we did not have enough data, or if we
     * try to decode 4 byte ASs in 2 byte format. Either way, return 4,
     * so that calller can try to decode each AS as of 4 bytes. If indeed
     * there was not enough data, it will crib and end the parse anyways.
     */
   return 4;
}