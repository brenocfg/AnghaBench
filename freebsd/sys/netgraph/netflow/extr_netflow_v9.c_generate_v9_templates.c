#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct netflow_v9_flowset_header {int dummy; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_7__ {int field_id; int field_length; } ;
struct TYPE_6__ {int flowsets_count; int* flowset_records; scalar_t__* v9_flowsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETFLOW_GENERAL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NETFLOW_V9_FLOW_V4_L4 ; 
 int NETFLOW_V9_FLOW_V6_L4 ; 
 int NETFLOW_V9_MAX_RESERVED_FLOWSET ; 
 int _NETFLOW_V9_TEMPLATE_SIZE (TYPE_3__*) ; 
 TYPE_3__* _netflow_v9_record_ipv4_tcp ; 
 TYPE_3__* _netflow_v9_record_ipv6_tcp ; 
 void* htons (int) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
generate_v9_templates(priv_p priv)
{
	uint16_t *p, *template_fields_cnt;
	int cnt;

	int flowset_size = sizeof(struct netflow_v9_flowset_header) +
		_NETFLOW_V9_TEMPLATE_SIZE(_netflow_v9_record_ipv4_tcp) + /* netflow_v9_record_ipv4_tcp */
		_NETFLOW_V9_TEMPLATE_SIZE(_netflow_v9_record_ipv6_tcp); /* netflow_v9_record_ipv6_tcp */

	priv->v9_flowsets[0] = malloc(flowset_size, M_NETFLOW_GENERAL, M_WAITOK | M_ZERO);

	if (flowset_size % 4)
		flowset_size += 4 - (flowset_size % 4); /* Padding to 4-byte boundary */

	priv->flowsets_count = 1;
	p = (uint16_t *)priv->v9_flowsets[0];
	*p++ = 0; /* Flowset ID, 0 is reserved for Template FlowSets  */
	*p++ = htons(flowset_size); /* Total FlowSet length */

	/*
	 * Most common TCP/UDP IPv4 template, ID = 256
	 */
	*p++ = htons(NETFLOW_V9_MAX_RESERVED_FLOWSET + NETFLOW_V9_FLOW_V4_L4);
	template_fields_cnt = p++;
	for (cnt = 0; _netflow_v9_record_ipv4_tcp[cnt].field_id != 0; cnt++) {
		*p++ = htons(_netflow_v9_record_ipv4_tcp[cnt].field_id);
		*p++ = htons(_netflow_v9_record_ipv4_tcp[cnt].field_length);
	}
	*template_fields_cnt = htons(cnt);

	/*
	 * TCP/UDP IPv6 template, ID = 257
	 */
	*p++ = htons(NETFLOW_V9_MAX_RESERVED_FLOWSET + NETFLOW_V9_FLOW_V6_L4);
	template_fields_cnt = p++;
	for (cnt = 0; _netflow_v9_record_ipv6_tcp[cnt].field_id != 0; cnt++) {
		*p++ = htons(_netflow_v9_record_ipv6_tcp[cnt].field_id);
		*p++ = htons(_netflow_v9_record_ipv6_tcp[cnt].field_length);
	}
	*template_fields_cnt = htons(cnt);

	priv->flowset_records[0] = 2;
}