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
typedef  int ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  LDNS_RR_TYPE_DNSKEY 130 
#define  LDNS_RR_TYPE_DS 129 
#define  LDNS_RR_TYPE_RRSIG 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int ldns_rr_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_dnskey_abbr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_ds_abbr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rrsig_abbr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
print_rr_list_abbr(FILE *fp, ldns_rr_list *rrlist, const char *usr) 
{
	size_t i;
	ldns_rr_type tp;

	for(i = 0; i < ldns_rr_list_rr_count(rrlist); i++) {
		tp = ldns_rr_get_type(ldns_rr_list_rr(rrlist, i));
		if (i == 0 && tp != LDNS_RR_TYPE_RRSIG) {
			if (usr) {
				fprintf(fp, "%s ", usr);
			}
		}
		switch(tp) {
		case LDNS_RR_TYPE_DNSKEY:
			print_dnskey_abbr(fp, ldns_rr_list_rr(rrlist, i));
			break;
		case LDNS_RR_TYPE_RRSIG:
			print_rrsig_abbr(fp, ldns_rr_list_rr(rrlist, i));
			break;
		case LDNS_RR_TYPE_DS:
			print_ds_abbr(fp, ldns_rr_list_rr(rrlist, i));
			break;
		default:
			/* not handled */
			break;
		}
		fputs("\n", fp);
	}
}