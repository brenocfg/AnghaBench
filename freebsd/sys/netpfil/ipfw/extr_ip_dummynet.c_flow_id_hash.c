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
typedef  int uint32_t ;
struct ipfw_flow_id {int dst_port; int src_port; int extra; int proto; int flow_id6; int dst_ip; int src_ip; int /*<<< orphan*/  src_ip6; int /*<<< orphan*/  dst_ip6; } ;

/* Variables and functions */
 scalar_t__ IS_IP6_FLOW_ID (struct ipfw_flow_id*) ; 

__attribute__((used)) static uint32_t
flow_id_hash(struct ipfw_flow_id *id)
{
    uint32_t i;

    if (IS_IP6_FLOW_ID(id)) {
	uint32_t *d = (uint32_t *)&id->dst_ip6;
	uint32_t *s = (uint32_t *)&id->src_ip6;
        i = (d[0]      ) ^ (d[1])       ^
            (d[2]      ) ^ (d[3])       ^
            (d[0] >> 15) ^ (d[1] >> 15) ^
            (d[2] >> 15) ^ (d[3] >> 15) ^
            (s[0] <<  1) ^ (s[1] <<  1) ^
            (s[2] <<  1) ^ (s[3] <<  1) ^
            (s[0] << 16) ^ (s[1] << 16) ^
            (s[2] << 16) ^ (s[3] << 16) ^
            (id->dst_port << 1) ^ (id->src_port) ^
	    (id->extra) ^
            (id->proto ) ^ (id->flow_id6);
    } else {
        i = (id->dst_ip)        ^ (id->dst_ip >> 15) ^
            (id->src_ip << 1)   ^ (id->src_ip >> 16) ^
	    (id->extra) ^
            (id->dst_port << 1) ^ (id->src_port)     ^ (id->proto);
    }
    return i;
}