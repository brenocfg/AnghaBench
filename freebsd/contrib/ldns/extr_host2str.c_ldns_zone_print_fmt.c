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
typedef  int /*<<< orphan*/  ldns_zone ;
typedef  int /*<<< orphan*/  ldns_output_format ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_rr_list_print_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_print_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_zone_rrs (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_zone_soa (int /*<<< orphan*/  const*) ; 

void
ldns_zone_print_fmt(FILE *output, 
		const ldns_output_format *fmt, const ldns_zone *z)
{
	if(ldns_zone_soa(z))
		ldns_rr_print_fmt(output, fmt, ldns_zone_soa(z));
	ldns_rr_list_print_fmt(output, fmt, ldns_zone_rrs(z));
}