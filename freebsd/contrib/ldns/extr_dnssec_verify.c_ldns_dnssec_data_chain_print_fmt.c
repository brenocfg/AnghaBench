#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* _name; } ;
typedef  TYPE_1__ ldns_rr_descriptor ;
typedef  int /*<<< orphan*/  ldns_output_format ;
struct TYPE_8__ {char* name; } ;
typedef  TYPE_2__ ldns_lookup_table ;
struct TYPE_9__ {scalar_t__ packet_qtype; int /*<<< orphan*/  signatures; int /*<<< orphan*/  rrset; scalar_t__ packet_nodata; scalar_t__ packet_rcode; struct TYPE_9__* parent; } ;
typedef  TYPE_3__ ldns_dnssec_data_chain ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* ldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_rcodes ; 
 TYPE_1__* ldns_rr_descript (scalar_t__) ; 
 int /*<<< orphan*/  ldns_rr_list_print_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ ) ; 

void
ldns_dnssec_data_chain_print_fmt(FILE *out, const ldns_output_format *fmt,
		const ldns_dnssec_data_chain *chain)
{
	ldns_lookup_table *rcode;
	const ldns_rr_descriptor *rr_descriptor;
	if (chain) {
		ldns_dnssec_data_chain_print_fmt(out, fmt, chain->parent);
		if (ldns_rr_list_rr_count(chain->rrset) > 0) {
			rcode = ldns_lookup_by_id(ldns_rcodes,
								 (int) chain->packet_rcode);
			if (rcode) {
				fprintf(out, ";; rcode: %s\n", rcode->name);
			}

			rr_descriptor = ldns_rr_descript(chain->packet_qtype);
			if (rr_descriptor && rr_descriptor->_name) {
				fprintf(out, ";; qtype: %s\n", rr_descriptor->_name);
			} else if (chain->packet_qtype != 0) {
				fprintf(out, "TYPE%u", 
					   chain->packet_qtype);
			}
			if (chain->packet_nodata) {
				fprintf(out, ";; NODATA response\n");
			}
			fprintf(out, "rrset:\n");
			ldns_rr_list_print_fmt(out, fmt, chain->rrset);
			fprintf(out, "sigs:\n");
			ldns_rr_list_print_fmt(out, fmt, chain->signatures);
			fprintf(out, "---\n");
		} else {
			fprintf(out, "<no data>\n");
		}
	}
}