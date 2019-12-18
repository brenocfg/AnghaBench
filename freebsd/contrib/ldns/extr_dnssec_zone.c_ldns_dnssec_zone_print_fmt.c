#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ ldns_output_format ;
struct TYPE_8__ {scalar_t__ names; scalar_t__ soa; } ;
typedef  TYPE_2__ ldns_dnssec_zone ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LDNS_COMMENT_LAYOUT ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldns_dnssec_name_find_rrset (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_name_name (scalar_t__) ; 
 int /*<<< orphan*/  ldns_dnssec_rrsets_print_fmt (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_dnssec_zone_names_print_fmt (int /*<<< orphan*/ *,TYPE_1__ const*,scalar_t__,int) ; 
 int /*<<< orphan*/  ldns_rdf_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ldns_dnssec_zone_print_fmt(FILE *out, const ldns_output_format *fmt,
	       const ldns_dnssec_zone *zone)
{
	if (zone) {
		if (zone->soa) {
			if ((fmt->flags & LDNS_COMMENT_LAYOUT)) {
				fprintf(out, ";; Zone: ");
				ldns_rdf_print(out, ldns_dnssec_name_name(
							zone->soa));
				fprintf(out, "\n;\n");
			}
			ldns_dnssec_rrsets_print_fmt(out, fmt,
					ldns_dnssec_name_find_rrset(
						zone->soa, 
						LDNS_RR_TYPE_SOA), 
					false);
			if ((fmt->flags & LDNS_COMMENT_LAYOUT))
				fprintf(out, ";\n");
		}

		if (zone->names) {
			ldns_dnssec_zone_names_print_fmt(out, fmt, 
					zone->names, false);
		}
	}
}