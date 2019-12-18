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
typedef  int /*<<< orphan*/  ldns_rr_list ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,int) ; 
 int ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_rr_verbose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_pkt_section_verbose(const char *name, ldns_rr_list *rrlist) {
    int i, cnt = ldns_rr_list_rr_count(rrlist);

    if (cnt == 0)
        return;
    printf(";; %s SECTION:\n", name);
    for (i = 0; i < cnt; i++)
        print_rr_verbose(ldns_rr_list_rr(rrlist, i));
    printf("\n");
}