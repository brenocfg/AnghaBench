#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int dname_len; int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct regional {int dummy; } ;
struct compress_tree_node {int labs; size_t offset; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_CREATE (size_t) ; 
 size_t PTR_MAX_OFFSET ; 
 int RETVAL_OK ; 
 int RETVAL_OUTMEM ; 
 int RETVAL_TRUNC ; 
 struct compress_tree_node* compress_tree_lookup (struct compress_tree_node**,int /*<<< orphan*/ *,int,struct compress_tree_node***) ; 
 int /*<<< orphan*/  compress_tree_store (int /*<<< orphan*/ *,int,size_t,struct regional*,struct compress_tree_node*,struct compress_tree_node**) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_compressed_dname (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct compress_tree_node*) ; 

__attribute__((used)) static int
compress_owner(struct ub_packed_rrset_key* key, sldns_buffer* pkt, 
	struct regional* region, struct compress_tree_node** tree, 
	size_t owner_pos, uint16_t* owner_ptr, int owner_labs)
{
	struct compress_tree_node* p;
	struct compress_tree_node** insertpt = NULL;
	if(!*owner_ptr) {
		/* compress first time dname */
		if((p = compress_tree_lookup(tree, key->rk.dname, 
			owner_labs, &insertpt))) {
			if(p->labs == owner_labs) 
				/* avoid ptr chains, since some software is
				 * not capable of decoding ptr after a ptr. */
				*owner_ptr = htons(PTR_CREATE(p->offset));
			if(!write_compressed_dname(pkt, key->rk.dname, 
				owner_labs, p))
				return RETVAL_TRUNC;
			/* check if typeclass+4 ttl + rdatalen is available */
			if(sldns_buffer_remaining(pkt) < 4+4+2)
				return RETVAL_TRUNC;
		} else {
			/* no compress */
			if(sldns_buffer_remaining(pkt) < key->rk.dname_len+4+4+2)
				return RETVAL_TRUNC;
			sldns_buffer_write(pkt, key->rk.dname, 
				key->rk.dname_len);
			if(owner_pos <= PTR_MAX_OFFSET)
				*owner_ptr = htons(PTR_CREATE(owner_pos));
		}
		if(!compress_tree_store(key->rk.dname, owner_labs, 
			owner_pos, region, p, insertpt))
			return RETVAL_OUTMEM;
	} else {
		/* always compress 2nd-further RRs in RRset */
		if(owner_labs == 1) {
			if(sldns_buffer_remaining(pkt) < 1+4+4+2) 
				return RETVAL_TRUNC;
			sldns_buffer_write_u8(pkt, 0);
		} else {
			if(sldns_buffer_remaining(pkt) < 2+4+4+2) 
				return RETVAL_TRUNC;
			sldns_buffer_write(pkt, owner_ptr, 2);
		}
	}
	return RETVAL_OK;
}