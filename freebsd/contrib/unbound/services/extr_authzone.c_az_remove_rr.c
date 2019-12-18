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
typedef  scalar_t__ uint16_t ;
struct auth_zone {scalar_t__ dclass; int /*<<< orphan*/  data; } ;
struct auth_data {int /*<<< orphan*/ * rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_data_delete (struct auth_data*) ; 
 int /*<<< orphan*/  az_domain_remove_rr (struct auth_data*,scalar_t__,int /*<<< orphan*/ *,size_t,int*) ; 
 struct auth_data* az_find_name (struct auth_zone*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,struct auth_data*) ; 
 scalar_t__ sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_rdatalen (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * sldns_wirerr_get_rdatawl (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static int
az_remove_rr(struct auth_zone* z, uint8_t* rr, size_t rr_len,
	size_t dname_len, int* nonexist)
{
	struct auth_data* node;
	uint8_t* dname = rr;
	uint16_t rr_type = sldns_wirerr_get_type(rr, rr_len, dname_len);
	uint16_t rr_class = sldns_wirerr_get_class(rr, rr_len, dname_len);
	size_t rdatalen = ((size_t)sldns_wirerr_get_rdatalen(rr, rr_len,
		dname_len))+2;
	/* rdata points to rdata prefixed with uint16 rdatalength */
	uint8_t* rdata = sldns_wirerr_get_rdatawl(rr, rr_len, dname_len);

	if(rr_class != z->dclass) {
		log_err("wrong class for RR");
		/* really also a nonexisting entry, because no records
		 * of that class in the zone, but return an error because
		 * getting records of the wrong class is a failure of the
		 * zone transfer */
		return 0;
	}
	node = az_find_name(z, dname, dname_len);
	if(!node) {
		/* node with that name does not exist */
		/* nonexisting entry, because no such name */
		*nonexist = 1;
		return 1;
	}
	if(!az_domain_remove_rr(node, rr_type, rdata, rdatalen, nonexist)) {
		/* alloc failure or so */
		return 0;
	}
	/* remove the node, if necessary */
	/* an rrsets==NULL entry is not kept around for empty nonterminals,
	 * and also parent nodes are not kept around, so we just delete it */
	if(node->rrsets == NULL) {
		(void)rbtree_delete(&z->data, node);
		auth_data_delete(node);
	}
	return 1;
}