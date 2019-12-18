#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct sa_query_result {unsigned int result_cnt; int /*<<< orphan*/  p_result_madw; } ;
struct sa_handle {int dummy; } ;
struct TYPE_4__ {scalar_t__ description; } ;
struct TYPE_5__ {int /*<<< orphan*/  lid; TYPE_1__ node_desc; } ;
typedef  TYPE_2__ ib_node_record_t ;

/* Variables and functions */
 int EHOSTDOWN ; 
 int /*<<< orphan*/  IB_SA_ATTR_NODERECORD ; 
 int /*<<< orphan*/  cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int get_all_records (struct sa_handle*,int /*<<< orphan*/ ,struct sa_query_result*) ; 
 int /*<<< orphan*/  sa_free_result_mad (struct sa_query_result*) ; 
 TYPE_2__* sa_get_query_rec (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int get_lid_from_name(struct sa_handle * h, const char *name, uint16_t * lid)
{
	ib_node_record_t *node_record = NULL;
	unsigned i;
	int ret;
	struct sa_query_result result;

	ret = get_all_records(h, IB_SA_ATTR_NODERECORD, &result);
	if (ret)
		return ret;

	ret = EHOSTDOWN;
	for (i = 0; i < result.result_cnt; i++) {
		node_record = sa_get_query_rec(result.p_result_madw, i);
		if (name
		    && strncmp(name, (char *)node_record->node_desc.description,
			       sizeof(node_record->node_desc.description)) ==
		    0) {
			*lid = cl_ntoh16(node_record->lid);
			ret = 0;
			break;
		}
	}
	sa_free_result_mad(&result);
	return ret;
}