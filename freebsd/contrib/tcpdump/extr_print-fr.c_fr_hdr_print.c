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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {scalar_t__ ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  fr_header_flag_values ; 
 int /*<<< orphan*/  nlpid_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
fr_hdr_print(netdissect_options *ndo,
             int length, u_int addr_len, u_int dlci, uint8_t *flags, uint16_t nlpid)
{
    if (ndo->ndo_qflag) {
        ND_PRINT((ndo, "Q.922, DLCI %u, length %u: ",
                     dlci,
                     length));
    } else {
        if (nlpid <= 0xff) /* if its smaller than 256 then its a NLPID */
            ND_PRINT((ndo, "Q.922, hdr-len %u, DLCI %u, Flags [%s], NLPID %s (0x%02x), length %u: ",
                         addr_len,
                         dlci,
                         bittok2str(fr_header_flag_values, "none", EXTRACT_32BITS(flags)),
                         tok2str(nlpid_values,"unknown", nlpid),
                         nlpid,
                         length));
        else /* must be an ethertype */
            ND_PRINT((ndo, "Q.922, hdr-len %u, DLCI %u, Flags [%s], cisco-ethertype %s (0x%04x), length %u: ",
                         addr_len,
                         dlci,
                         bittok2str(fr_header_flag_values, "none", EXTRACT_32BITS(flags)),
                         tok2str(ethertype_values, "unknown", nlpid),
                         nlpid,
                         length));
    }
}