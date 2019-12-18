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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {size_t dname_len; int /*<<< orphan*/  dname; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct reply_info {size_t rrset_count; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ub_packed_rrset_key* reply_find_rrset(struct reply_info* rep,
	uint8_t* name, size_t namelen, uint16_t type, uint16_t dclass)
{
	size_t i;
	for(i=0; i<rep->rrset_count; i++) {
		struct ub_packed_rrset_key* s = rep->rrsets[i];
		if(ntohs(s->rk.type) == type && 
			ntohs(s->rk.rrset_class) == dclass && 
			namelen == s->rk.dname_len &&
			query_dname_compare(name, s->rk.dname) == 0) {
			return s;
		}
	}
	return NULL;
}