#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * now; int /*<<< orphan*/  rrset_cache; } ;
struct worker {TYPE_1__ env; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; } ;
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 char* load_qinfo (char*,struct query_info*,struct regional*) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warn (char*,char*) ; 
 struct ub_packed_rrset_key* packed_rrset_copy_region (struct ub_packed_rrset_key*,struct regional*,int /*<<< orphan*/ ) ; 
 struct ub_packed_rrset_key* rrset_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  ssl_read_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
load_ref(RES* ssl, sldns_buffer* buf, struct worker* worker, 
	struct regional *region, struct ub_packed_rrset_key** rrset, 
	int* go_on)
{
	char* s = (char*)sldns_buffer_begin(buf);
	struct query_info qinfo;
	unsigned int flags;
	struct ub_packed_rrset_key* k;

	/* read line */
	if(!ssl_read_buf(ssl, buf))
		return 0;
	if(strncmp(s, "BADREF", 6) == 0) {
		*go_on = 0; /* its bad, skip it and skip message */
		return 1;
	}

	s = load_qinfo(s, &qinfo, region);
	if(!s) {
		return 0;
	}
	if(sscanf(s, " %u", &flags) != 1) {
		log_warn("error cannot parse flags: %s", s);
		return 0;
	}

	/* lookup in cache */
	k = rrset_cache_lookup(worker->env.rrset_cache, qinfo.qname,
		qinfo.qname_len, qinfo.qtype, qinfo.qclass,
		(uint32_t)flags, *worker->env.now, 0);
	if(!k) {
		/* not found or expired */
		*go_on = 0;
		return 1;
	}

	/* store in result */
	*rrset = packed_rrset_copy_region(k, region, *worker->env.now);
	lock_rw_unlock(&k->entry.lock);

	return (*rrset != NULL);
}