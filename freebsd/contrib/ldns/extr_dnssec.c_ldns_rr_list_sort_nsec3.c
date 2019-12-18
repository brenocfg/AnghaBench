#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  _rrs; } ;
typedef  TYPE_1__ ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_rr_list_rr_count (TYPE_1__*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_rr_compare_nsec3 ; 

void
ldns_rr_list_sort_nsec3(ldns_rr_list *unsorted)
{
	qsort(unsorted->_rrs,
	      ldns_rr_list_rr_count(unsorted),
	      sizeof(ldns_rr *),
	      qsort_rr_compare_nsec3);
}