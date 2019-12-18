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
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct ipfw_flow_id {int dummy; } ;
struct dyn_data {scalar_t__ expire; void* hashval; void* fibnum; void* rulenum; void* ruleid; void* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  MATCH_FORWARD ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_dyn_data_zone ; 
 scalar_t__ V_dyn_syn_lifetime ; 
 int /*<<< orphan*/  dyn_update_proto_state (struct dyn_data*,struct ipfw_flow_id const*,void const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ last_log ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_uptime ; 
 struct dyn_data* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dyn_data *
dyn_alloc_dyndata(void *parent, uint32_t ruleid, uint16_t rulenum,
    const struct ipfw_flow_id *pkt, const void *ulp, int pktlen,
    uint32_t hashval, uint16_t fibnum)
{
	struct dyn_data *data;

	data = uma_zalloc(V_dyn_data_zone, M_NOWAIT | M_ZERO);
	if (data == NULL) {
		if (last_log != time_uptime) {
			last_log = time_uptime;
			log(LOG_DEBUG,
			    "ipfw: Cannot allocate dynamic state, "
			    "consider increasing net.inet.ip.fw.dyn_max\n");
		}
		return (NULL);
	}

	data->parent = parent;
	data->ruleid = ruleid;
	data->rulenum = rulenum;
	data->fibnum = fibnum;
	data->hashval = hashval;
	data->expire = time_uptime + V_dyn_syn_lifetime;
	dyn_update_proto_state(data, pkt, ulp, pktlen, MATCH_FORWARD);
	return (data);
}