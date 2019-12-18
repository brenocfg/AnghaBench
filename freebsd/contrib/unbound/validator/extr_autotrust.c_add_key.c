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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct trust_anchor {size_t namelen; TYPE_1__* autr; int /*<<< orphan*/ * name; } ;
struct autr_ta {struct autr_ta* next; } ;
struct TYPE_2__ {struct autr_ta* keys; } ;

/* Variables and functions */
 size_t LDNS_RR_CLASS_IN ; 
 size_t LDNS_RR_TYPE_DNSKEY ; 
 struct autr_ta* autr_ta_create (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct autr_ta*
add_key(struct trust_anchor* tp, uint32_t ttl, uint8_t* rdata, size_t rdata_len)
{
	struct autr_ta* ta;
	uint8_t* rr;
	size_t rr_len, dname_len;
	uint16_t rrtype = htons(LDNS_RR_TYPE_DNSKEY);
	uint16_t rrclass = htons(LDNS_RR_CLASS_IN);
	uint16_t rdlen = htons(rdata_len);
	dname_len = tp->namelen;
	ttl = htonl(ttl);
	rr_len = dname_len + 10 /* type,class,ttl,rdatalen */ + rdata_len;
	rr = (uint8_t*)malloc(rr_len);
	if(!rr) return NULL;
	memmove(rr, tp->name, tp->namelen);
	memmove(rr+dname_len, &rrtype, 2);
	memmove(rr+dname_len+2, &rrclass, 2);
	memmove(rr+dname_len+4, &ttl, 4);
	memmove(rr+dname_len+8, &rdlen, 2);
	memmove(rr+dname_len+10, rdata, rdata_len);
	ta = autr_ta_create(rr, rr_len, dname_len);
	if(!ta) {
		/* rr freed in autr_ta_create */
		return NULL;
	}
	/* link in, tp already locked */
	ta->next = tp->autr->keys;
	tp->autr->keys = ta;
	return ta;
}