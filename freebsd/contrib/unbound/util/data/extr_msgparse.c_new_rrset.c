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
typedef  void* uint16_t ;
struct rrset_parse {int hash; size_t dname_len; scalar_t__ rrsig_last; scalar_t__ rrsig_first; scalar_t__ rrsig_count; scalar_t__ rr_last; scalar_t__ rr_first; scalar_t__ size; scalar_t__ rr_count; int /*<<< orphan*/  flags; void* rrset_class; void* type; int /*<<< orphan*/ * dname; int /*<<< orphan*/  section; struct rrset_parse* rrset_all_next; struct rrset_parse* rrset_bucket_next; } ;
struct regional {int dummy; } ;
struct msg_parse {struct rrset_parse* rrset_last; struct rrset_parse* rrset_first; struct rrset_parse** hashtable; } ;
typedef  int /*<<< orphan*/  sldns_pkt_section ;
typedef  int hashvalue_type ;

/* Variables and functions */
 int PARSE_TABLE_SIZE ; 
 struct rrset_parse* regional_alloc (struct regional*,int) ; 

__attribute__((used)) static struct rrset_parse* 
new_rrset(struct msg_parse* msg, uint8_t* dname, size_t dnamelen, 
	uint16_t type, uint16_t dclass, hashvalue_type hash, 
	uint32_t rrset_flags, sldns_pkt_section section, 
	struct regional* region)
{
	struct rrset_parse* p = regional_alloc(region, sizeof(*p));
	if(!p) return NULL;
	p->rrset_bucket_next = msg->hashtable[hash & (PARSE_TABLE_SIZE-1)];
	msg->hashtable[hash & (PARSE_TABLE_SIZE-1)] = p;
	p->rrset_all_next = 0;
	if(msg->rrset_last)
		msg->rrset_last->rrset_all_next = p;
	else 	msg->rrset_first = p;
	msg->rrset_last = p;
	p->hash = hash;
	p->section = section;
	p->dname = dname;
	p->dname_len = dnamelen;
	p->type = type;
	p->rrset_class = dclass;
	p->flags = rrset_flags;
	p->rr_count = 0;
	p->size = 0;
	p->rr_first = 0;
	p->rr_last = 0;
	p->rrsig_count = 0;
	p->rrsig_first = 0;
	p->rrsig_last = 0;
	return p;
}