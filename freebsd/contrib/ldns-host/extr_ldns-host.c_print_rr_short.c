#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_3__ {scalar_t__ type; char* text; } ;

/* Variables and functions */
 size_t countof (TYPE_1__*) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 size_t ldns_rr_rd_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  print_rdf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rdf_nodot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rr_type (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* rr_types ; 

__attribute__((used)) static void
print_rr_short(ldns_rr *rr) {
    ldns_rr_type type = ldns_rr_get_type(rr);
    size_t i, rdcnt = ldns_rr_rd_count(rr);

    print_rdf_nodot(ldns_rr_owner(rr));
    printf(" ");
    for (i = 0; i < countof(rr_types); i++) {
        if (rr_types[i].type == type) {
            printf("%s", rr_types[i].text);
            goto found;
        }
    }

    printf("has ");
    print_rr_type(type);
    printf(" record");

found:
    for (i = 0; i < rdcnt; i++) {
        printf(" ");
        print_rdf(ldns_rr_rdf(rr, i));
    }
    printf("\n");
}