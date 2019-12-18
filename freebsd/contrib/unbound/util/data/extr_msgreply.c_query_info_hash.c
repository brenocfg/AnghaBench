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
typedef  int uint16_t ;
struct query_info {scalar_t__ qtype; scalar_t__ qclass; int /*<<< orphan*/  qname; } ;
typedef  int hashvalue_type ;

/* Variables and functions */
 int BIT_CD ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int dname_query_hash (int /*<<< orphan*/ ,int) ; 
 int hashlittle (scalar_t__*,int,int) ; 

hashvalue_type
query_info_hash(struct query_info *q, uint16_t flags)
{
	hashvalue_type h = 0xab;
	h = hashlittle(&q->qtype, sizeof(q->qtype), h);
	if(q->qtype == LDNS_RR_TYPE_AAAA && (flags&BIT_CD))
		h++;
	h = hashlittle(&q->qclass, sizeof(q->qclass), h);
	h = dname_query_hash(q->qname, h);
	return h;
}