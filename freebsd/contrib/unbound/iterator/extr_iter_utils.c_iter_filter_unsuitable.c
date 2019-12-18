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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct module_env {int /*<<< orphan*/  infra_cache; } ;
struct iter_env {int /*<<< orphan*/  supports_ipv4; int /*<<< orphan*/  supports_ipv6; int /*<<< orphan*/  donotq; } ;
struct delegpt_addr {scalar_t__ lame; scalar_t__ dnsseclame; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; scalar_t__ bogus; } ;

/* Variables and functions */
 int UNKNOWN_SERVER_NICENESS ; 
 int USEFUL_SERVER_TOP_TIMEOUT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ addr_is_ip6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ donotq_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ infra_get_lame_rtt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int*,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,char*,char*,char*,char*) ; 

__attribute__((used)) static int
iter_filter_unsuitable(struct iter_env* iter_env, struct module_env* env,
	uint8_t* name, size_t namelen, uint16_t qtype, time_t now, 
	struct delegpt_addr* a)
{
	int rtt, lame, reclame, dnsseclame;
	if(a->bogus)
		return -1; /* address of server is bogus */
	if(donotq_lookup(iter_env->donotq, &a->addr, a->addrlen)) {
		log_addr(VERB_ALGO, "skip addr on the donotquery list",
			&a->addr, a->addrlen);
		return -1; /* server is on the donotquery list */
	}
	if(!iter_env->supports_ipv6 && addr_is_ip6(&a->addr, a->addrlen)) {
		return -1; /* there is no ip6 available */
	}
	if(!iter_env->supports_ipv4 && !addr_is_ip6(&a->addr, a->addrlen)) {
		return -1; /* there is no ip4 available */
	}
	/* check lameness - need zone , class info */
	if(infra_get_lame_rtt(env->infra_cache, &a->addr, a->addrlen, 
		name, namelen, qtype, &lame, &dnsseclame, &reclame, 
		&rtt, now)) {
		log_addr(VERB_ALGO, "servselect", &a->addr, a->addrlen);
		verbose(VERB_ALGO, "   rtt=%d%s%s%s%s", rtt,
			lame?" LAME":"",
			dnsseclame?" DNSSEC_LAME":"",
			reclame?" REC_LAME":"",
			a->lame?" ADDR_LAME":"");
		if(lame)
			return -1; /* server is lame */
		else if(rtt >= USEFUL_SERVER_TOP_TIMEOUT)
			/* server is unresponsive,
			 * we used to return TOP_TIMEOUT, but fairly useless,
			 * because if == TOP_TIMEOUT is dropped because
			 * blacklisted later, instead, remove it here, so
			 * other choices (that are not blacklisted) can be
			 * tried */
			return -1;
		/* select remainder from worst to best */
		else if(reclame)
			return rtt+USEFUL_SERVER_TOP_TIMEOUT*3; /* nonpref */
		else if(dnsseclame || a->dnsseclame)
			return rtt+USEFUL_SERVER_TOP_TIMEOUT*2; /* nonpref */
		else if(a->lame)
			return rtt+USEFUL_SERVER_TOP_TIMEOUT+1; /* nonpref */
		else	return rtt;
	}
	/* no server information present */
	if(a->dnsseclame)
		return UNKNOWN_SERVER_NICENESS+USEFUL_SERVER_TOP_TIMEOUT*2; /* nonpref */
	else if(a->lame)
		return USEFUL_SERVER_TOP_TIMEOUT+1+UNKNOWN_SERVER_NICENESS; /* nonpref */
	return UNKNOWN_SERVER_NICENESS;
}