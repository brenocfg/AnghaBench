#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ub_result {int ttl; char** data; int* len; int /*<<< orphan*/ * canonname; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dname; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct reply_info {scalar_t__ rrset_count; size_t an_numrrsets; scalar_t__ ttl; TYPE_4__** rrsets; } ;
struct query_info {int /*<<< orphan*/  qname; } ;
struct packed_rrset_data {int count; int* rr_len; scalar_t__ ttl; scalar_t__* rr_data; } ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_3__ entry; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fill_canon (struct ub_result*,int /*<<< orphan*/ *) ; 
 char* memdup (scalar_t__,size_t) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fill_res(struct ub_result* res, struct ub_packed_rrset_key* answer,
	uint8_t* finalcname, struct query_info* rq, struct reply_info* rep)
{
	size_t i;
	struct packed_rrset_data* data;
	res->ttl = 0;
	if(!answer) {
		if(finalcname) {
			if(!fill_canon(res, finalcname))
				return 0; /* out of memory */
		}
		if(rep->rrset_count != 0)
			res->ttl = (int)rep->ttl;
		res->data = (char**)calloc(1, sizeof(char*));
		res->len = (int*)calloc(1, sizeof(int));
		return (res->data && res->len);
	}
	data = (struct packed_rrset_data*)answer->entry.data;
	if(query_dname_compare(rq->qname, answer->rk.dname) != 0) {
		if(!fill_canon(res, answer->rk.dname))
			return 0; /* out of memory */
	} else	res->canonname = NULL;
	res->data = (char**)calloc(data->count+1, sizeof(char*));
	res->len = (int*)calloc(data->count+1, sizeof(int));
	if(!res->data || !res->len)
		return 0; /* out of memory */
	for(i=0; i<data->count; i++) {
		/* remove rdlength from rdata */
		res->len[i] = (int)(data->rr_len[i] - 2);
		res->data[i] = memdup(data->rr_data[i]+2, (size_t)res->len[i]);
		if(!res->data[i])
			return 0; /* out of memory */
	}
	/* ttl for positive answers, from CNAME and answer RRs */
	if(data->count != 0) {
		size_t j;
		res->ttl = (int)data->ttl;
		for(j=0; j<rep->an_numrrsets; j++) {
			struct packed_rrset_data* d =
				(struct packed_rrset_data*)rep->rrsets[j]->
				entry.data;
			if((int)d->ttl < res->ttl)
				res->ttl = (int)d->ttl;
		}
	}
	/* ttl for negative answers */
	if(data->count == 0 && rep->rrset_count != 0)
		res->ttl = (int)rep->ttl;
	res->data[data->count] = NULL;
	res->len[data->count] = 0;
	return 1;
}