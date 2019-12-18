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
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ ldns_lookup_table ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  LDNS_RR_TYPE_DNSKEY 130 
#define  LDNS_RR_TYPE_DS 129 
#define  LDNS_RR_TYPE_RRSIG 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* ldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_rr_classes ; 
 int ldns_rr_get_class (int /*<<< orphan*/ *) ; 
 int ldns_rr_get_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_class_type(FILE *fp, ldns_rr *r)
{
	ldns_lookup_table *lt;
        lt = ldns_lookup_by_id(ldns_rr_classes, ldns_rr_get_class(r));
        if (lt) {
               	fprintf(fp, " %s", lt->name);
        } else {
        	fprintf(fp, " CLASS%d", ldns_rr_get_class(r));
        }
	/* okay not THE way - but the quickest */
	switch (ldns_rr_get_type(r)) {
		case LDNS_RR_TYPE_RRSIG:
			fprintf(fp, " RRSIG ");
			break;
		case LDNS_RR_TYPE_DNSKEY:
			fprintf(fp, " DNSKEY ");
			break;
		case LDNS_RR_TYPE_DS:
			fprintf(fp, " DS ");
			break;
		default:
			break;
	}
}