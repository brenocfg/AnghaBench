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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lwapp_transport_header {int version; int /*<<< orphan*/  frag_id; int /*<<< orphan*/  length; } ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ LWAPP_EXTRACT_CONTROL_BIT (int) ; 
 int /*<<< orphan*/  LWAPP_EXTRACT_RID (int) ; 
 scalar_t__ LWAPP_EXTRACT_VERSION (int) ; 
 scalar_t__ LWAPP_VERSION ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct lwapp_transport_header const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lwapp_header_bits_values ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int /*<<< orphan*/  const*,char*,int) ; 

void
lwapp_data_print(netdissect_options *ndo,
                 const u_char *pptr, u_int len)
{
    const struct lwapp_transport_header *lwapp_trans_header;
    const u_char *tptr;
    int tlen;

    tptr=pptr;

    /* check if enough bytes for AP identity */
    ND_TCHECK2(*tptr, 6);
    lwapp_trans_header = (const struct lwapp_transport_header *)pptr;
    ND_TCHECK(*lwapp_trans_header);

    /*
     * Sanity checking of the header.
     */
    if (LWAPP_EXTRACT_VERSION(lwapp_trans_header->version) != LWAPP_VERSION) {
        ND_PRINT((ndo, "LWAPP version %u packet not supported",
               LWAPP_EXTRACT_VERSION(lwapp_trans_header->version)));
        return;
    }

    /* non-verbose */
    if (ndo->ndo_vflag < 1) {
        ND_PRINT((ndo, "LWAPPv%u, %s frame, Flags [%s], length %u",
               LWAPP_EXTRACT_VERSION(lwapp_trans_header->version),
               LWAPP_EXTRACT_CONTROL_BIT(lwapp_trans_header->version) ? "Control" : "Data",
               bittok2str(lwapp_header_bits_values,"none",(lwapp_trans_header->version)&0x07),
               len));
        return;
    }

    /* ok they seem to want to know everything - lets fully decode it */
    tlen=EXTRACT_16BITS(lwapp_trans_header->length);

    ND_PRINT((ndo, "LWAPPv%u, %s frame, Radio-id  %u, Flags [%s], Frag-id  %u, length %u",
           LWAPP_EXTRACT_VERSION(lwapp_trans_header->version),
           LWAPP_EXTRACT_CONTROL_BIT(lwapp_trans_header->version) ? "Control" : "Data",
           LWAPP_EXTRACT_RID(lwapp_trans_header->version),
           bittok2str(lwapp_header_bits_values,"none",(lwapp_trans_header->version)&0x07),
           lwapp_trans_header->frag_id,
           tlen));

    tptr+=sizeof(const struct lwapp_transport_header);
    tlen-=sizeof(const struct lwapp_transport_header);

    /* FIX - An IEEE 802.11 frame follows - hexdump for now */
    print_unknown_data(ndo, tptr, "\n\t", tlen);

    return;

 trunc:
    ND_PRINT((ndo, "\n\t\t packet exceeded snapshot"));
}