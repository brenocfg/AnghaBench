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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct auth_zone {scalar_t__ dclass; } ;
struct auth_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  az_domain_add_rr (struct auth_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int*) ; 
 struct auth_data* az_domain_find_or_create (struct auth_zone*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_rdatalen (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * sldns_wirerr_get_rdatawl (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_ttl (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static int
az_insert_rr(struct auth_zone* z, uint8_t* rr, size_t rr_len,
	size_t dname_len, int* duplicate)
{
	struct auth_data* node;
	uint8_t* dname = rr;
	uint16_t rr_type = sldns_wirerr_get_type(rr, rr_len, dname_len);
	uint16_t rr_class = sldns_wirerr_get_class(rr, rr_len, dname_len);
	uint32_t rr_ttl = sldns_wirerr_get_ttl(rr, rr_len, dname_len);
	size_t rdatalen = ((size_t)sldns_wirerr_get_rdatalen(rr, rr_len,
		dname_len))+2;
	/* rdata points to rdata prefixed with uint16 rdatalength */
	uint8_t* rdata = sldns_wirerr_get_rdatawl(rr, rr_len, dname_len);

	if(rr_class != z->dclass) {
		log_err("wrong class for RR");
		return 0;
	}
	if(!(node=az_domain_find_or_create(z, dname, dname_len))) {
		log_err("cannot create domain");
		return 0;
	}
	if(!az_domain_add_rr(node, rr_type, rr_ttl, rdata, rdatalen,
		duplicate)) {
		log_err("cannot add RR to domain");
		return 0;
	}
	return 1;
}