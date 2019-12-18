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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 size_t LDNS_MAX_DOMAINLEN ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  dname_remove_labels (int /*<<< orphan*/ **,size_t*,int) ; 

uint8_t* dname_get_shared_topdomain(uint8_t* d1, uint8_t* d2)
{
	int labs1, labs2, m;
	size_t len = LDNS_MAX_DOMAINLEN;
	labs1 = dname_count_labels(d1);
	labs2 = dname_count_labels(d2);
	(void)dname_lab_cmp(d1, labs1, d2, labs2, &m);
	dname_remove_labels(&d1, &len, labs1-m);
	return d1;
}