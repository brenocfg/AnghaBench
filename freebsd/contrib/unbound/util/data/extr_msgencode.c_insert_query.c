#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct regional {int dummy; } ;
struct query_info {size_t qname_len; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; TYPE_3__* local_alias; int /*<<< orphan*/ * qname; } ;
struct compress_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_6__ {TYPE_2__* rrset; } ;
struct TYPE_4__ {size_t dname_len; int /*<<< orphan*/ * dname; } ;
struct TYPE_5__ {TYPE_1__ rk; } ;

/* Variables and functions */
 int RETVAL_OK ; 
 int RETVAL_OUTMEM ; 
 int RETVAL_TRUNC ; 
 int /*<<< orphan*/  compress_tree_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regional*,int /*<<< orphan*/ *,struct compress_tree_node**) ; 
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
insert_query(struct query_info* qinfo, struct compress_tree_node** tree, 
	sldns_buffer* buffer, struct regional* region)
{
	uint8_t* qname = qinfo->local_alias ?
		qinfo->local_alias->rrset->rk.dname : qinfo->qname;
	size_t qname_len = qinfo->local_alias ?
		qinfo->local_alias->rrset->rk.dname_len : qinfo->qname_len;
	if(sldns_buffer_remaining(buffer) < 
		qinfo->qname_len+sizeof(uint16_t)*2)
		return RETVAL_TRUNC; /* buffer too small */
	/* the query is the first name inserted into the tree */
	if(!compress_tree_store(qname, dname_count_labels(qname),
		sldns_buffer_position(buffer), region, NULL, tree))
		return RETVAL_OUTMEM;
	if(sldns_buffer_current(buffer) == qname)
		sldns_buffer_skip(buffer, (ssize_t)qname_len);
	else	sldns_buffer_write(buffer, qname, qname_len);
	sldns_buffer_write_u16(buffer, qinfo->qtype);
	sldns_buffer_write_u16(buffer, qinfo->qclass);
	return RETVAL_OK;
}