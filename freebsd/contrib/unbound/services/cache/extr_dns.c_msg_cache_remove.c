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
typedef  void* uint16_t ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * local_alias; void* qclass; void* qtype; int /*<<< orphan*/ * qname; } ;
struct module_env {int /*<<< orphan*/  msg_cache; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 int /*<<< orphan*/  query_info_hash (struct query_info*,void*) ; 
 int /*<<< orphan*/  slabhash_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct query_info*) ; 

void
msg_cache_remove(struct module_env* env, uint8_t* qname, size_t qnamelen, 
	uint16_t qtype, uint16_t qclass, uint16_t flags)
{
	struct query_info k;
	hashvalue_type h;

	k.qname = qname;
	k.qname_len = qnamelen;
	k.qtype = qtype;
	k.qclass = qclass;
	k.local_alias = NULL;
	h = query_info_hash(&k, flags);
	slabhash_remove(env->msg_cache, h, &k);
}