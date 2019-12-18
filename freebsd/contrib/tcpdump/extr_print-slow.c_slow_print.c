#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int const LACP_VERSION ; 
 int const MARKER_VERSION ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
#define  SLOW_PROTO_LACP 130 
#define  SLOW_PROTO_MARKER 129 
#define  SLOW_PROTO_OAM 128 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int const*,char*,int) ; 
 int /*<<< orphan*/  slow_marker_lacp_print (TYPE_1__*,int const*,int,int) ; 
 int /*<<< orphan*/  slow_oam_print (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  slow_proto_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

void
slow_print(netdissect_options *ndo,
           register const u_char *pptr, register u_int len)
{
    int print_version;
    u_int subtype;

    if (len < 1)
        goto tooshort;
    ND_TCHECK(*pptr);
    subtype = *pptr;

    /*
     * Sanity checking of the header.
     */
    switch (subtype) {
    case SLOW_PROTO_LACP:
        if (len < 2)
            goto tooshort;
        ND_TCHECK(*(pptr+1));
        if (*(pptr+1) != LACP_VERSION) {
            ND_PRINT((ndo, "LACP version %u packet not supported", *(pptr+1)));
            return;
        }
        print_version = 1;
        break;

    case SLOW_PROTO_MARKER:
        if (len < 2)
            goto tooshort;
        ND_TCHECK(*(pptr+1));
        if (*(pptr+1) != MARKER_VERSION) {
            ND_PRINT((ndo, "MARKER version %u packet not supported", *(pptr+1)));
            return;
        }
        print_version = 1;
        break;

    case SLOW_PROTO_OAM: /* fall through */
        print_version = 0;
        break;

    default:
        /* print basic information and exit */
        print_version = -1;
        break;
    }

    if (print_version == 1) {
        ND_PRINT((ndo, "%sv%u, length %u",
               tok2str(slow_proto_values, "unknown (%u)", subtype),
               *(pptr+1),
               len));
    } else {
        /* some slow protos don't have a version number in the header */
        ND_PRINT((ndo, "%s, length %u",
               tok2str(slow_proto_values, "unknown (%u)", subtype),
               len));
    }

    /* unrecognized subtype */
    if (print_version == -1) {
        print_unknown_data(ndo, pptr, "\n\t", len);
        return;
    }

    if (!ndo->ndo_vflag)
        return;

    switch (subtype) {
    default: /* should not happen */
        break;

    case SLOW_PROTO_OAM:
        /* skip subtype */
        len -= 1;
        pptr += 1;
        slow_oam_print(ndo, pptr, len);
        break;

    case SLOW_PROTO_LACP:   /* LACP and MARKER share the same semantics */
    case SLOW_PROTO_MARKER:
        /* skip subtype and version */
        len -= 2;
        pptr += 2;
        slow_marker_lacp_print(ndo, pptr, len, subtype);
        break;
    }
    return;

tooshort:
    if (!ndo->ndo_vflag)
        ND_PRINT((ndo, " (packet is too short)"));
    else
        ND_PRINT((ndo, "\n\t\t packet is too short"));
    return;

trunc:
    if (!ndo->ndo_vflag)
        ND_PRINT((ndo, " (packet exceeded snapshot)"));
    else
        ND_PRINT((ndo, "\n\t\t packet exceeded snapshot"));
}