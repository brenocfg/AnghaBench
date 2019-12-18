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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ldns_dnssec_rrsets ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 

ldns_status
ldns_dnssec_rrsets_set_type(ldns_dnssec_rrsets *rrsets,
					   ldns_rr_type type)
{
	if (rrsets) {
		rrsets->type = type;
		return LDNS_STATUS_OK;
	}
	return LDNS_STATUS_ERR;
}