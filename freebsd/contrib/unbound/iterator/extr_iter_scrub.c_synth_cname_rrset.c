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
typedef  int /*<<< orphan*/  uint16_t ;
struct rrset_parse {size_t dname_len; int rr_count; int size; int outside_packet; int /*<<< orphan*/ * ttl_data; struct rrset_parse* rr_first; struct rrset_parse* rrset_all_next; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/ * dname; int /*<<< orphan*/  hash; int /*<<< orphan*/  section; struct rrset_parse* rr_last; } ;
struct rr_parse {size_t dname_len; int rr_count; int size; int outside_packet; int /*<<< orphan*/ * ttl_data; struct rr_parse* rr_first; struct rr_parse* rrset_all_next; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/ * dname; int /*<<< orphan*/  hash; int /*<<< orphan*/  section; struct rr_parse* rr_last; } ;
struct regional {int dummy; } ;
struct msg_parse {int /*<<< orphan*/  an_rrsets; int /*<<< orphan*/  rrset_count; struct rrset_parse* rrset_last; struct rrset_parse* rrset_first; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_CNAME ; 
 int /*<<< orphan*/  dname_pkt_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (struct rrset_parse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pkt_hash_rrset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regional_alloc (struct regional*,int) ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rrset_parse*
synth_cname_rrset(uint8_t** sname, size_t* snamelen, uint8_t* alias, 
	size_t aliaslen, struct regional* region, struct msg_parse* msg, 
	struct rrset_parse* rrset, struct rrset_parse* prev,
	struct rrset_parse* nx, sldns_buffer* pkt)
{
	struct rrset_parse* cn = (struct rrset_parse*)regional_alloc(region,
		sizeof(struct rrset_parse));
	if(!cn)
		return NULL;
	memset(cn, 0, sizeof(*cn));
	cn->rr_first = (struct rr_parse*)regional_alloc(region, 
		sizeof(struct rr_parse));
	if(!cn->rr_first)
		return NULL;
	cn->rr_last = cn->rr_first;
	/* CNAME from sname to alias */
	cn->dname = (uint8_t*)regional_alloc(region, *snamelen);
	if(!cn->dname)
		return NULL;
	dname_pkt_copy(pkt, cn->dname, *sname);
	cn->dname_len = *snamelen;
	cn->type = LDNS_RR_TYPE_CNAME;
	cn->section = rrset->section;
	cn->rrset_class = rrset->rrset_class;
	cn->rr_count = 1;
	cn->size = sizeof(uint16_t) + aliaslen;
	cn->hash=pkt_hash_rrset(pkt, cn->dname, cn->type, cn->rrset_class, 0);
	/* allocate TTL + rdatalen + uncompressed dname */
	memset(cn->rr_first, 0, sizeof(struct rr_parse));
	cn->rr_first->outside_packet = 1;
	cn->rr_first->ttl_data = (uint8_t*)regional_alloc(region, 
		sizeof(uint32_t)+sizeof(uint16_t)+aliaslen);
	if(!cn->rr_first->ttl_data)
		return NULL;
	sldns_write_uint32(cn->rr_first->ttl_data, 0); /* TTL = 0 */
	sldns_write_uint16(cn->rr_first->ttl_data+4, aliaslen);
	memmove(cn->rr_first->ttl_data+6, alias, aliaslen);
	cn->rr_first->size = sizeof(uint16_t)+aliaslen;

	/* link it in */
	cn->rrset_all_next = nx;
	if(prev)
		prev->rrset_all_next = cn;
	else	msg->rrset_first = cn;
	if(nx == NULL)
		msg->rrset_last = cn;
	msg->rrset_count ++;
	msg->an_rrsets++;
	/* it is not inserted in the msg hashtable. */

	*sname = cn->rr_first->ttl_data + sizeof(uint32_t)+sizeof(uint16_t);
	*snamelen = aliaslen;
	return cn;
}