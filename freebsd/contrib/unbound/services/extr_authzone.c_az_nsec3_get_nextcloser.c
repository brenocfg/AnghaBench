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
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_labels (int /*<<< orphan*/ **,size_t*,int) ; 
 int /*<<< orphan*/  dname_strict_subdomain (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
az_nsec3_get_nextcloser(uint8_t* cenm, uint8_t* qname, size_t qname_len,
	uint8_t** nx, size_t* nxlen)
{
	int celabs = dname_count_labels(cenm);
	int qlabs = dname_count_labels(qname);
	int strip = qlabs - celabs -1;
	log_assert(dname_strict_subdomain(qname, qlabs, cenm, celabs));
	*nx = qname;
	*nxlen = qname_len;
	if(strip>0)
		dname_remove_labels(nx, nxlen, strip);
}