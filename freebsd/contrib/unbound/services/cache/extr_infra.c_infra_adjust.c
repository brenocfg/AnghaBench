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
struct infra_key {int dummy; } ;
struct infra_data {int dummy; } ;
struct infra_cache {int /*<<< orphan*/  domain_limits; int /*<<< orphan*/  client_ip_rates; int /*<<< orphan*/  domain_rates; int /*<<< orphan*/  hosts; int /*<<< orphan*/  host_ttl; } ;
struct config_file {int infra_cache_numhosts; size_t ratelimit_size; size_t ip_ratelimit_size; int /*<<< orphan*/  ip_ratelimit_slabs; int /*<<< orphan*/  ratelimit_slabs; int /*<<< orphan*/  infra_cache_slabs; int /*<<< orphan*/  ip_ratelimit; int /*<<< orphan*/  ratelimit; int /*<<< orphan*/  host_ttl; } ;

/* Variables and functions */
 int INFRA_BYTES_NAME ; 
 int /*<<< orphan*/  domain_limit_free ; 
 struct infra_cache* infra_create (struct config_file*) ; 
 int /*<<< orphan*/  infra_delete (struct infra_cache*) ; 
 int /*<<< orphan*/  infra_dp_ratelimit ; 
 int /*<<< orphan*/  infra_ip_ratelimit ; 
 int /*<<< orphan*/  setup_domain_limits (struct infra_cache*,struct config_file*) ; 
 int /*<<< orphan*/  slabhash_is_size (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct infra_cache* 
infra_adjust(struct infra_cache* infra, struct config_file* cfg)
{
	size_t maxmem;
	if(!infra)
		return infra_create(cfg);
	infra->host_ttl = cfg->host_ttl;
	infra_dp_ratelimit = cfg->ratelimit;
	infra_ip_ratelimit = cfg->ip_ratelimit;
	maxmem = cfg->infra_cache_numhosts * (sizeof(struct infra_key)+
		sizeof(struct infra_data)+INFRA_BYTES_NAME);
	/* divide cachesize by slabs and multiply by slabs, because if the
	 * cachesize is not an even multiple of slabs, that is the resulting
	 * size of the slabhash */
	if(!slabhash_is_size(infra->hosts, maxmem, cfg->infra_cache_slabs) ||
	   !slabhash_is_size(infra->domain_rates, cfg->ratelimit_size,
	   	cfg->ratelimit_slabs) ||
	   !slabhash_is_size(infra->client_ip_rates, cfg->ip_ratelimit_size,
	   	cfg->ip_ratelimit_slabs)) {
		infra_delete(infra);
		infra = infra_create(cfg);
	} else {
		/* reapply domain limits */
		traverse_postorder(&infra->domain_limits, domain_limit_free,
			NULL);
		if(!setup_domain_limits(infra, cfg)) {
			infra_delete(infra);
			return NULL;
		}
	}
	return infra;
}