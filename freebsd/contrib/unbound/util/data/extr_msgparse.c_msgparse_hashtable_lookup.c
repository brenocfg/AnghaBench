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
struct rrset_parse {struct rrset_parse* rrset_bucket_next; } ;
struct msg_parse {struct rrset_parse** hashtable; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int hashvalue_type ;

/* Variables and functions */
 int PARSE_TABLE_SIZE ; 
 scalar_t__ rrset_parse_equals (struct rrset_parse*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rrset_parse*
msgparse_hashtable_lookup(struct msg_parse* msg, sldns_buffer* pkt, 
	hashvalue_type h, uint32_t rrset_flags, uint8_t* dname,
	size_t dnamelen, uint16_t type, uint16_t dclass)
{
	struct rrset_parse* p = msg->hashtable[h & (PARSE_TABLE_SIZE-1)];
	while(p) {
		if(rrset_parse_equals(p, pkt, h, rrset_flags, dname, dnamelen,
			type, dclass))
			return p;
		p = p->rrset_bucket_next;
	}
	return NULL;
}