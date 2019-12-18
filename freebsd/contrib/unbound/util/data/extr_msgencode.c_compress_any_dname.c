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
struct regional {int dummy; } ;
struct compress_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int RETVAL_OK ; 
 int RETVAL_OUTMEM ; 
 int RETVAL_TRUNC ; 
 struct compress_tree_node* compress_tree_lookup (struct compress_tree_node**,int /*<<< orphan*/ *,int,struct compress_tree_node***) ; 
 int /*<<< orphan*/  compress_tree_store (int /*<<< orphan*/ *,int,size_t,struct regional*,struct compress_tree_node*,struct compress_tree_node**) ; 
 int /*<<< orphan*/  dname_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_compressed_dname (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct compress_tree_node*) ; 

__attribute__((used)) static int
compress_any_dname(uint8_t* dname, sldns_buffer* pkt, int labs, 
	struct regional* region, struct compress_tree_node** tree)
{
	struct compress_tree_node* p;
	struct compress_tree_node** insertpt = NULL;
	size_t pos = sldns_buffer_position(pkt);
	if((p = compress_tree_lookup(tree, dname, labs, &insertpt))) {
		if(!write_compressed_dname(pkt, dname, labs, p))
			return RETVAL_TRUNC;
	} else {
		if(!dname_buffer_write(pkt, dname))
			return RETVAL_TRUNC;
	}
	if(!compress_tree_store(dname, labs, pos, region, p, insertpt))
		return RETVAL_OUTMEM;
	return RETVAL_OK;
}