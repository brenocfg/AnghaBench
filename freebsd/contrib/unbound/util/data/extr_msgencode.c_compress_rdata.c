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
typedef  scalar_t__ uint8_t ;
struct regional {int dummy; } ;
struct compress_tree_node {int dummy; } ;
struct TYPE_3__ {int* _wireformat; scalar_t__ _dname_count; } ;
typedef  TYPE_1__ sldns_rr_descriptor ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
#define  LDNS_RDF_TYPE_DNAME 129 
#define  LDNS_RDF_TYPE_STR 128 
 int RETVAL_OK ; 
 int RETVAL_TRUNC ; 
 int compress_any_dname (scalar_t__*,int /*<<< orphan*/ *,int,struct regional*,struct compress_tree_node**) ; 
 int dname_count_size_labels (scalar_t__*,size_t*) ; 
 size_t get_rdf_size (int) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static int
compress_rdata(sldns_buffer* pkt, uint8_t* rdata, size_t todolen, 
	struct regional* region, struct compress_tree_node** tree, 
	const sldns_rr_descriptor* desc)
{
	int labs, r, rdf = 0;
	size_t dname_len, len, pos = sldns_buffer_position(pkt);
	uint8_t count = desc->_dname_count;

	sldns_buffer_skip(pkt, 2); /* rdata len fill in later */
	/* space for rdatalen checked for already */
	rdata += 2;
	todolen -= 2;
	while(todolen > 0 && count) {
		switch(desc->_wireformat[rdf]) {
		case LDNS_RDF_TYPE_DNAME:
			labs = dname_count_size_labels(rdata, &dname_len);
			if((r=compress_any_dname(rdata, pkt, labs, region, 
				tree)) != RETVAL_OK)
				return r;
			rdata += dname_len;
			todolen -= dname_len;
			count--;
			len = 0;
			break;
		case LDNS_RDF_TYPE_STR:
			len = *rdata + 1;
			break;
		default:
			len = get_rdf_size(desc->_wireformat[rdf]);
		}
		if(len) {
			/* copy over */
			if(sldns_buffer_remaining(pkt) < len)
				return RETVAL_TRUNC;
			sldns_buffer_write(pkt, rdata, len);
			todolen -= len;
			rdata += len;
		}
		rdf++;
	}
	/* copy remainder */
	if(todolen > 0) {
		if(sldns_buffer_remaining(pkt) < todolen)
			return RETVAL_TRUNC;
		sldns_buffer_write(pkt, rdata, todolen);
	}

	/* set rdata len */
	sldns_buffer_write_u16_at(pkt, pos, sldns_buffer_position(pkt)-pos-2);
	return RETVAL_OK;
}