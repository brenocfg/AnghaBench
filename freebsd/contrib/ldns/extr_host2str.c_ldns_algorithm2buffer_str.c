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
struct TYPE_3__ {scalar_t__ name; } ;
typedef  TYPE_1__ ldns_lookup_table ;
typedef  int /*<<< orphan*/  ldns_buffer ;
typedef  scalar_t__ ldns_algorithm ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_algorithms ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_lookup_by_id (int /*<<< orphan*/ ,scalar_t__) ; 

ldns_status
ldns_algorithm2buffer_str(ldns_buffer *output,
                          ldns_algorithm algorithm)
{
	ldns_lookup_table *lt = ldns_lookup_by_id(ldns_algorithms,
	                                          algorithm);
	if (lt && lt->name) {
		ldns_buffer_printf(output, "%s", lt->name);
	} else {
		ldns_buffer_printf(output, "ALG%u", algorithm);
	}
	return ldns_buffer_status(output);
}