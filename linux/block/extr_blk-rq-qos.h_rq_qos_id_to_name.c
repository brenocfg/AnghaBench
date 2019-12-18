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
typedef  enum rq_qos_id { ____Placeholder_rq_qos_id } rq_qos_id ;

/* Variables and functions */
#define  RQ_QOS_COST 130 
#define  RQ_QOS_LATENCY 129 
#define  RQ_QOS_WBT 128 

__attribute__((used)) static inline const char *rq_qos_id_to_name(enum rq_qos_id id)
{
	switch (id) {
	case RQ_QOS_WBT:
		return "wbt";
	case RQ_QOS_LATENCY:
		return "latency";
	case RQ_QOS_COST:
		return "cost";
	}
	return "unknown";
}