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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lsa6_hdr {int /*<<< orphan*/  ls_stateid; int /*<<< orphan*/  ls_type; int /*<<< orphan*/  ls_length; int /*<<< orphan*/  ls_age; int /*<<< orphan*/  ls_seq; int /*<<< orphan*/  ls_router; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ospf6_print_ls_type (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ospf6_print_lshdr(netdissect_options *ndo,
                  register const struct lsa6_hdr *lshp, const u_char *dataend)
{
	if ((const u_char *)(lshp + 1) > dataend)
		goto trunc;
	ND_TCHECK(lshp->ls_type);
	ND_TCHECK(lshp->ls_seq);

	ND_PRINT((ndo, "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u",
               ipaddr_string(ndo, &lshp->ls_router),
               EXTRACT_32BITS(&lshp->ls_seq),
               EXTRACT_16BITS(&lshp->ls_age),
               EXTRACT_16BITS(&lshp->ls_length)-(u_int)sizeof(struct lsa6_hdr)));

	ospf6_print_ls_type(ndo, EXTRACT_16BITS(&lshp->ls_type), &lshp->ls_stateid);

	return (0);
trunc:
	return (1);
}