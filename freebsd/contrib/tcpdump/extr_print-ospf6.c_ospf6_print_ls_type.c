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
typedef  int u_int ;
typedef  int /*<<< orphan*/  rtrid_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int LS_SCOPE_MASK ; 
 int LS_TYPE_MASK ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ospf6_ls_scope_values ; 
 int /*<<< orphan*/  ospf6_lsa_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
ospf6_print_ls_type(netdissect_options *ndo,
                    register u_int ls_type, register const rtrid_t *ls_stateid)
{
        ND_PRINT((ndo, "\n\t    %s LSA (%d), %s Scope%s, LSA-ID %s",
               tok2str(ospf6_lsa_values, "Unknown", ls_type & LS_TYPE_MASK),
               ls_type & LS_TYPE_MASK,
               tok2str(ospf6_ls_scope_values, "Unknown", ls_type & LS_SCOPE_MASK),
               ls_type &0x8000 ? ", transitive" : "", /* U-bit */
               ipaddr_string(ndo, ls_stateid)));
}