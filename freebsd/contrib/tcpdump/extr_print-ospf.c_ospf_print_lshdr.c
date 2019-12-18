#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {int opaque_type; int /*<<< orphan*/  opaque_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsa_id; TYPE_1__ opaque_field; } ;
struct lsa_hdr {int ls_length; int ls_seq; int ls_age; int ls_type; int ls_options; TYPE_2__ un_lsa_id; int /*<<< orphan*/  ls_router; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int*) ; 
 int /*<<< orphan*/  EXTRACT_24BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int*) ; 
#define  LS_TYPE_OPAQUE_AL 130 
#define  LS_TYPE_OPAQUE_DW 129 
#define  LS_TYPE_OPAQUE_LL 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsa_opaque_values ; 
 int /*<<< orphan*/  lsa_values ; 
 int /*<<< orphan*/  ospf_option_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ospf_print_lshdr(netdissect_options *ndo,
                 register const struct lsa_hdr *lshp)
{
        u_int ls_length;

        ND_TCHECK(lshp->ls_length);
        ls_length = EXTRACT_16BITS(&lshp->ls_length);
        if (ls_length < sizeof(struct lsa_hdr)) {
                ND_PRINT((ndo, "\n\t    Bogus length %u < header (%lu)", ls_length,
                    (unsigned long)sizeof(struct lsa_hdr)));
                return(-1);
        }

        ND_TCHECK(lshp->ls_seq); /* XXX - ls_length check checked this */
        ND_PRINT((ndo, "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u",
                  ipaddr_string(ndo, &lshp->ls_router),
                  EXTRACT_32BITS(&lshp->ls_seq),
                  EXTRACT_16BITS(&lshp->ls_age),
                  ls_length - (u_int)sizeof(struct lsa_hdr)));

        ND_TCHECK(lshp->ls_type); /* XXX - ls_length check checked this */
        switch (lshp->ls_type) {
        /* the LSA header for opaque LSAs was slightly changed */
        case LS_TYPE_OPAQUE_LL:
        case LS_TYPE_OPAQUE_AL:
        case LS_TYPE_OPAQUE_DW:
            ND_PRINT((ndo, "\n\t    %s LSA (%d), Opaque-Type %s LSA (%u), Opaque-ID %u",
                   tok2str(lsa_values,"unknown",lshp->ls_type),
                   lshp->ls_type,

		   tok2str(lsa_opaque_values,
			   "unknown",
			   *(&lshp->un_lsa_id.opaque_field.opaque_type)),
		   *(&lshp->un_lsa_id.opaque_field.opaque_type),
		   EXTRACT_24BITS(&lshp->un_lsa_id.opaque_field.opaque_id)

                   ));
            break;

        /* all other LSA types use regular style LSA headers */
        default:
            ND_PRINT((ndo, "\n\t    %s LSA (%d), LSA-ID: %s",
                   tok2str(lsa_values,"unknown",lshp->ls_type),
                   lshp->ls_type,
                   ipaddr_string(ndo, &lshp->un_lsa_id.lsa_id)));
            break;
        }

        ND_TCHECK(lshp->ls_options); /* XXX - ls_length check checked this */
        ND_PRINT((ndo, "\n\t    Options: [%s]", bittok2str(ospf_option_values, "none", lshp->ls_options)));

        return (ls_length);
trunc:
	return (-1);
}