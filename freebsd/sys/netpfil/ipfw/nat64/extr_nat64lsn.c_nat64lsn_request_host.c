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
struct ipfw_flow_id {int dummy; } ;
struct nat64lsn_job_item {int /*<<< orphan*/  src6_hval; int /*<<< orphan*/  proto; int /*<<< orphan*/  port; int /*<<< orphan*/  faddr; struct ipfw_flow_id f_id; struct mbuf* m; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct nat64lsn_cfg {TYPE_1__ base; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int IP_FW_DENY ; 
 int /*<<< orphan*/  JTYPE_NEWHOST ; 
 int /*<<< orphan*/  NAT64STAT_INC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhostsreq ; 
 struct nat64lsn_job_item* nat64lsn_create_job (struct nat64lsn_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nat64lsn_enqueue_job (struct nat64lsn_cfg*,struct nat64lsn_job_item*) ; 

__attribute__((used)) static int
nat64lsn_request_host(struct nat64lsn_cfg *cfg,
    const struct ipfw_flow_id *f_id, struct mbuf **mp, uint32_t hval,
    in_addr_t faddr, uint16_t port, uint8_t proto)
{
	struct nat64lsn_job_item *ji;

	ji = nat64lsn_create_job(cfg, JTYPE_NEWHOST);
	if (ji != NULL) {
		ji->m = *mp;
		ji->f_id = *f_id;
		ji->faddr = faddr;
		ji->port = port;
		ji->proto = proto;
		ji->src6_hval = hval;

		nat64lsn_enqueue_job(cfg, ji);
		NAT64STAT_INC(&cfg->base.stats, jhostsreq);
		*mp = NULL;
	}
	return (IP_FW_DENY);
}