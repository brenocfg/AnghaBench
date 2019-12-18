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
typedef  int /*<<< orphan*/  ldns_rr_class ;
struct TYPE_3__ {int /*<<< orphan*/  const name; } ;
typedef  TYPE_1__ ldns_lookup_table ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_lookup_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ldns_rr_classes ; 

ldns_status
ldns_rr_class2buffer_str(ldns_buffer *output,
                         const ldns_rr_class klass)
{
	ldns_lookup_table *lt;

	lt = ldns_lookup_by_id(ldns_rr_classes, klass);
	if (lt) {
		ldns_buffer_printf(output, "%s", lt->name);
	} else {
		ldns_buffer_printf(output, "CLASS%d", klass);
	}
	return ldns_buffer_status(output);
}