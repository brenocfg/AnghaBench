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
struct trust_anchor {scalar_t__ numDS; scalar_t__ numDNSKEY; int /*<<< orphan*/  lock; } ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct module_env {int /*<<< orphan*/  anchors; } ;

/* Variables and functions */
 struct trust_anchor* anchors_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

int
iter_qname_indicates_dnssec(struct module_env* env, struct query_info *qinfo)
{
	struct trust_anchor* a;
	if(!env || !env->anchors || !qinfo || !qinfo->qname)
		return 0;
	/* a trust anchor exists above the name? */
	if((a=anchors_lookup(env->anchors, qinfo->qname, qinfo->qname_len,
		qinfo->qclass))) { 
		if(a->numDS == 0 && a->numDNSKEY == 0) {
			/* insecure trust point */
			lock_basic_unlock(&a->lock);
			return 0;
		}
		lock_basic_unlock(&a->lock);
		return 1;
	}
	/* no trust anchor above it. */
	return 0;
}