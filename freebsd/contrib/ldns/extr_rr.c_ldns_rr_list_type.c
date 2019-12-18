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
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_rr_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 

ldns_rr_type
ldns_rr_list_type(const ldns_rr_list *rr_list)
{
	if (rr_list && ldns_rr_list_rr_count(rr_list) > 0) {
		return ldns_rr_get_type(ldns_rr_list_rr(rr_list, 0));
	} else {
		return 0;
	}
}