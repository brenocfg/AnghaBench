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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct reply_info {int dummy; } ;
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
struct module_env {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dns_cache_store (struct module_env*,struct query_info*,struct reply_info*,int,int /*<<< orphan*/ ,int,struct regional*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 

void 
iter_dns_store(struct module_env* env, struct query_info* msgqinf,
	struct reply_info* msgrep, int is_referral, time_t leeway, int pside,
	struct regional* region, uint16_t flags)
{
	if(!dns_cache_store(env, msgqinf, msgrep, is_referral, leeway,
		pside, region, flags))
		log_err("out of memory: cannot store data in cache");
}