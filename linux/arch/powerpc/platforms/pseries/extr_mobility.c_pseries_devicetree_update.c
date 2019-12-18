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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  ADD_DT_NODE 130 
#define  DELETE_DT_NODE 129 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NODE_ACTION_MASK ; 
 int NODE_COUNT_MASK ; 
 int /*<<< orphan*/  PRRN_SCOPE ; 
 int /*<<< orphan*/  RTAS_DATA_BUF_SIZE ; 
 int RTAS_UNKNOWN_SERVICE ; 
#define  UPDATE_DT_NODE 128 
 int /*<<< orphan*/  add_dt_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  delete_dt_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mobility_rtas_call (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prrn_update_node (int /*<<< orphan*/ ) ; 
 int rtas_token (char*) ; 
 int /*<<< orphan*/  update_dt_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pseries_devicetree_update(s32 scope)
{
	char *rtas_buf;
	__be32 *data;
	int update_nodes_token;
	int rc;

	update_nodes_token = rtas_token("ibm,update-nodes");
	if (update_nodes_token == RTAS_UNKNOWN_SERVICE)
		return -EINVAL;

	rtas_buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	if (!rtas_buf)
		return -ENOMEM;

	do {
		rc = mobility_rtas_call(update_nodes_token, rtas_buf, scope);
		if (rc && rc != 1)
			break;

		data = (__be32 *)rtas_buf + 4;
		while (be32_to_cpu(*data) & NODE_ACTION_MASK) {
			int i;
			u32 action = be32_to_cpu(*data) & NODE_ACTION_MASK;
			u32 node_count = be32_to_cpu(*data) & NODE_COUNT_MASK;

			data++;

			for (i = 0; i < node_count; i++) {
				__be32 phandle = *data++;
				__be32 drc_index;

				switch (action) {
				case DELETE_DT_NODE:
					delete_dt_node(phandle);
					break;
				case UPDATE_DT_NODE:
					update_dt_node(phandle, scope);

					if (scope == PRRN_SCOPE)
						prrn_update_node(phandle);

					break;
				case ADD_DT_NODE:
					drc_index = *data++;
					add_dt_node(phandle, drc_index);
					break;
				}

				cond_resched();
			}
		}

		cond_resched();
	} while (rc == 1);

	kfree(rtas_buf);
	return rc;
}