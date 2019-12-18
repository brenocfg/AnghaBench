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
typedef  int ldns_rr_type ;
struct TYPE_3__ {int const _name; } ;
typedef  TYPE_1__ ldns_rr_descriptor ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
#define  LDNS_RR_TYPE_ANY 132 
#define  LDNS_RR_TYPE_AXFR 131 
#define  LDNS_RR_TYPE_IXFR 130 
#define  LDNS_RR_TYPE_MAILA 129 
#define  LDNS_RR_TYPE_MAILB 128 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_rr_descript (int const) ; 

ldns_status
ldns_rr_type2buffer_str(ldns_buffer *output, const ldns_rr_type type)
{
	const ldns_rr_descriptor *descriptor;

	descriptor = ldns_rr_descript(type);

	switch (type) {
		case LDNS_RR_TYPE_IXFR:
			ldns_buffer_printf(output, "IXFR");
			break;
		case LDNS_RR_TYPE_AXFR:
			ldns_buffer_printf(output, "AXFR");
			break;
		case LDNS_RR_TYPE_MAILA:
			ldns_buffer_printf(output, "MAILA");
			break;
		case LDNS_RR_TYPE_MAILB:
			ldns_buffer_printf(output, "MAILB");
			break;
		case LDNS_RR_TYPE_ANY:
			ldns_buffer_printf(output, "ANY");
			break;
		default:
			if (descriptor && descriptor->_name) {
				ldns_buffer_printf(output, "%s", descriptor->_name);
			} else {
				ldns_buffer_printf(output, "TYPE%u", type);
			}
	}
	return ldns_buffer_status(output);
}